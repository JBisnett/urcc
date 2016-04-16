require "ast/ast_scope.rb"
require "ast/ast_stat.rb"
require "ast/ast_expr.rb"
require "ruby-graphviz"

module PassModule
  class BasicBlock
    include Enumerable
    attr_reader :label
    attr_reader :stmts, :val2expr, :expr2val, :val2rval
    attr_accessor :output_defs, :input_defs
    attr_accessor :out
    attr_accessor :out_blocks
    attr_accessor :parent
    attr_accessor :req_stmt
    def initialize s, p
      @label = s
      @stmts = []
      @out = nil
      @out_blocks = []
      @val2expr = Hash.new
      @expr2val = Hash.new
      @val2rval = Hash.new
      @output_defs = Hash.new {|hash, key| hash[key] = Array.new}
      @input_defs = Hash.new {|hash, key| hash[key] = Array.new}
      @parent = p
      @req_stmt = []
    end
    def add_stmt chld
      stmts << chld
    end
    def <<(chld)
      add_stmt chld
    end
    def to_s
      "#{node.label}:\n\n#{stmts.map(&:c_dump).join("")}"
    end
    def each(&block)
      stmts.each(&block)
    end 
    #need to account for loops
    def add_input_hash in_hash
      in_hash.keys.each do |k|
        @input_defs[k] = @input_defs[k] + in_hash[k]
        @output_defs[k] = @output_defs[k] + in_hash[k]
      end
    end 
    def process_defs

      def add_def a, use
        @output_defs[a.c_dump].each do |defi|
          @parent.def_use_list["[#{[a.c_dump, defi.c_dump, use.c_dump].map(&:chomp).join", "}]"] = true
        end
      end
      
      reject{|s| s.instance_of?(Ast::GotoStat) || s.instance_of?(Ast::LabelStat)}.each do |as|
        if as.instance_of? Ast::AssignStat
          if as.is_exp?  
            if as.rhs.instance_of? Ast::Call
              as.rhs.para_list_copy.each do |arg| 
                add_def arg, as
              end
            else
              puts "Not a call"
            end
          else
            if as.rhs.instance_of? Ast::VarAcc
              add_def as.rhs, as
            elsif as.rhs.instance_of? Ast::OpExpr
              if as.rhs.rand2 != nil
                add_def as.rhs.rand1, as
                add_def as.rhs.rand2, as
              elsif
                add_def as.rhs.rand1, as
              end
            end
            @output_defs[as.lhs.c_dump] = [as] if as.instance_of? Ast::AssignStat
          end
        else
          add_def as.expr, as if as.expr != nil
        end
      end
      out_blocks.each{|chld| chld.add_input_hash @output_defs}
    end
    def print
      each{|stmt| puts stmt.c_dump}
    end

  end

  class Function
    attr_reader :labels, :entry_bb, :exit_bbs, :val, :outputs
    attr_accessor :def_use_list, :old_def_use_list
    include Enumerable
    def each (&block)
      basic_blocks.each(&block)
    end
    def basic_blocks
      labels.values
    end

    #give each bb a label
    def start_bb stmt
      #split up bb if jumps into code
      if @cur_bb != nil
        fin_bb stmt
      end
      @cur_bb = BasicBlock.new stmt, self
      @labels[stmt.label] = @cur_bb
    end 

    #end on a return, goto, or additional label
    def fin_bb stmt
      @cur_bb.out = stmt
      @last_bb = @cur_bb
      @cur_bb = nil
    end

    def process_stmt stmt
      case stmt.class.name
      when "Ast::GotoStat"
        fin_bb stmt
      when "Ast::ReturnStat"
        @cur_bb << stmt
        @cur_bb.req_stmt << stmt
        fin_bb stmt
      when "Ast::AssignStat"
        @cur_bb << stmt
        if stmt.rhs.instance_of? Ast::Call
          @cur_bb.req_stmt << stmt
        end
      when "Ast::LabelStat"
        start_bb stmt
      end
    end

    # link all the basic blocks to their children
    def link_bbs
      basic_blocks.each do |bb|
        out_stmt = bb.out
        case out_stmt.class.name
        when "Ast::GotoStat"
          if out_stmt.is_cond?
            bb.out_blocks = bb.out_blocks << @labels[bb.out.target_true]
            bb.out_blocks = bb.out_blocks <<  @labels[bb.out.target_false]
          else
            bb.out_blocks = bb.out_blocks <<  @labels[bb.out.target]
          end
        when "Ast::ReturnStat"
          @exit_bbs << bb
        end
      end
      @entry_bb = @labels["lbl_entry"]
    end

    def print_def_use
      @def_use_list.keys.each{|x| $f.puts x}
    end

    def do_def_use
      def do_def_use_imp
        each do |bb|
          bb.process_defs
        end
        if @def_use_list.keys != @old_def_use_list.keys
          @def_use_list.keys.each {|s| @old_def_use_list[s] = true}
          do_def_use_imp
        end
      end
      do_def_use_imp
      #@def_use_list.keys.each{|x| puts x}
      #puts
    end

    def req_stmts
        basic_blocks.map do |bb|
          bb.req_stmt
        end.flatten
    end

    def print_bb_req_stmts
      basic_blocks.each do |bb|
        puts bb.label.c_dump
        puts bb.req_stmt.map(&:c_dump)
        puts
      end
    end

    def initialize func_node
      @labels = Hash.new
      @cur_bb = nil
      @val = func_node
      @exit_bbs = []
      @def_use_list = {}
      @old_def_use_list = {}
      func_node.each do |stmt|
        process_stmt stmt
      end
      link_bbs
    end 
  end

  Pass = Proc.new do |prog|
    $f = File.open "defs.out", "w+"
    funcs = prog.children_copy.map do |chld|
      Function.new chld
    end
    funcs.each do |func|
      func.do_def_use
      puts func.val.c_dump
      func.print_bb_req_stmts
      puts
    end
  end
end
