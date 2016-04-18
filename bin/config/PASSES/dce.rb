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
    attr_accessor :out_blocks, :in_blocks
    attr_accessor :parent
    attr_accessor :stmt_req
    attr_accessor :use2def
    attr_reader :loc
    def initialize s, p
      @label = s
      @stmts = []
      @out = nil
      @out_blocks = []
      @in_blocks = []
      @val2expr = Hash.new
      @expr2val = Hash.new
      @val2rval = Hash.new
      @output_defs = Hash.new {|hash, key| hash[key] = Array.new}
      @input_defs = Hash.new {|hash, key| hash[key] = Array.new}
      @parent = p
      @stmt_req = Hash.new
      @use2def = Hash.new {|hash, key| hash[key] = Array.new}
    end
    def unmark stmt
      puts "potential error" if @stmt_req[stmt.c_dump] != nil
      @stmt_req[stmt.c_dump] = false
    end
    def mark stmt
      @stmt_req[stmt.c_dump] = true
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

      def add_use a, use
        if a.instance_of? Ast::VarAcc
          if a.dim > 0
            a.children_copy.each do |chld|
              add_use chld, use
            end
          end
        end
        @output_defs[a.c_dump].each do |defi|
          @parent.def_use_list["[#{[a.c_dump, defi.c_dump, use.c_dump].map(&:chomp).join", "}]"] = [a, defi, use]
          @use2def[use.c_dump] = @use2def[use.c_dump] << defi #might need to be an array?
        end
      end

      reject{|s| s.instance_of?(Ast::LabelStat)}.each do |as|
        if as.instance_of? Ast::AssignStat
          if as.lhs.instance_of? Ast::DerefAcc
            add_use as.lhs, as
          end
          if as.rhs.instance_of? Ast::Call
            as.rhs.para_list_copy.each do |arg| 
              add_use arg, as
            end
          elsif as.rhs.is_a? Ast::VarAcc #cover DerefAcc
            add_use as.rhs, as
          elsif as.rhs.instance_of? Ast::OpExpr
            if as.rhs.rand2 != nil
              add_use as.rhs.rand1, as
              add_use as.rhs.rand2, as
            elsif
              if as.rhs.rator == '&'
                @output_defs['*'+as.lhs.c_dump]=[as]
              end
              add_use as.rhs.rand1, as
            end
          end
          @output_defs[as.lhs.c_dump] = [as] if as.lhs != nil
        elsif out.instance_of?(Ast::GotoStat)
          add_use out.condition, out if out.condition != nil
        else
          add_use as.expr, as if as.expr != nil
        end
      end
      out_blocks.each{|chld| chld.add_input_hash @output_defs}
    end

    def start_infection 
      #puts @stmt_req
      @stmt_req.each do |key, val|
        if val
          @use2def[key].each do |defi|
            defi.basic_block.infect defi
          end
        end
      end
    end

    def infect stmt
      if stmt_req[stmt.c_dump] != true
        mark stmt
        arr = @use2def[stmt.c_dump]
        arr.each do |defi|
          defi.basic_block.infect defi
        end
      end
    end

    def purge_dead
      @loc = 0
      each do |stmt|
        if @stmt_req[stmt.c_dump] != true
          stmt.detach_me
        else
          @loc += 1
        end
      end
    end

    def print
      each{|stmt| puts stmt.c_dump}
    end

  end

  class Function
    attr_reader :labels, :entry_bb, :exit_bbs, :val
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
        stmt.basic_block = @cur_bb
        stmt.basic_block.mark stmt
        @cur_bb << stmt
        fin_bb stmt
      when "Ast::ReturnStat"
        @cur_bb << stmt
        @cur_bb.mark stmt
        stmt.basic_block = @cur_bb
        fin_bb stmt
      when "Ast::AssignStat"
        @cur_bb << stmt
        stmt.basic_block = @cur_bb
        if stmt.rhs.instance_of? Ast::Call
          stmt.basic_block.mark stmt
        elsif stmt.lhs.var.parent.id == "prog" #is a global variable
          stmt.basic_block.mark stmt
        else
          stmt.basic_block.unmark stmt
        end
      when "Ast::LabelStat"
        start_bb stmt
        stmt.basic_block = @cur_bb
        stmt.basic_block.mark stmt
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
            @labels[bb.out.target_true].in_blocks = @labels[bb.out.target_true].in_blocks << bb
            @labels[bb.out.target_false].in_blocks = @labels[bb.out.target_false].in_blocks << bb
          else
            bb.out_blocks = bb.out_blocks << @labels[bb.out.target]
            @labels[bb.out.target].in_blocks = @labels[bb.out.target].in_blocks << bb
          end
        when "Ast::ReturnStat"
          @exit_bbs << bb
        end
      end
      @entry_bb = @labels["lbl_entry"]
    end

    def print_def_use
      @def_use_list.keys.each{|x| puts x}
      puts
      #basic_blocks.each do |bb|
      #  puts bb.use2def.map{|key, val| [key, val].join(",")}
      #end
    end

    def print_stmt_req
      each do |bb|
        bb.stmt_req.each do |key, val|
          puts [val,key].join("\t")
        end
        puts
      end
    end

    def do_def_use
      def do_def_use_imp
        each do |bb|
          bb.process_defs
        end
        if @def_use_list.keys != @old_def_use_list.keys
          @def_use_list.keys.each {|s| @old_def_use_list[s] = @def_use_list[s]}
          do_def_use_imp
        end
      end
      do_def_use_imp
      #@def_use_list.keys.each{|x| puts x}
      #puts
    end
    #make this iterative too
    def do_dead_code_elim
      def dce_imp bb
        bb.start_infection
      end
      each do |bb|
        dce_imp bb
      end
      each do |bb|
        bb.purge_dead
      end
      inject(0) do |sum, bb| sum + bb.loc end
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
    funcs = prog.children_copy.map do |chld|
      Function.new chld
    end
    puts "INST COUNT:#{funcs.inject(0) do |sum, func|
      func.do_def_use
      func.print_def_use
      res = func.do_dead_code_elim
      func.print_stmt_req
      sum + res
    end}"
  end
end
