require "ast/ast_scope.rb"
require "ast/ast_stat.rb"
require "ast/ast_expr.rb"
require "ruby-graphviz"

module PassModule

  class BasicBlock
    include Enumerable
    attr_reader :node
    attr_reader :stmts, :val2expr, :expr2val, :val2rval
    attr_accessor :out
    attr_accessor :out_blocks
    def initialize s
      @label = s
      @stmts = []
      @out = nil
      @out_blocks = []
      @val2expr = Hash.new
      @expr2val = Hash.new
      @val2rval = Hash.new

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
    def process
      stmts.select{|x| x.is_a? Ast::AssignStat}.each do |x|
        if x.rhs.instance_of? Ast::OpExpr
          expr = nil
          rhs1 = x.rhs.rand1
          rhs1 = @val2rval[rhs1.c_dump] if @val2rval[rhs1.c_dump] != nil
          if x.rhs.is_binary?
            rhs2 = x.rhs.rand2
            rhs2 = @val2rval[rhs2.c_dump] if @val2rval[rhs2.c_dump] != nil

            if x.rhs.rator == '+' || x.rhs.rator == '*'
              expr = [x.rhs.rator] + [rhs1.c_dump, rhs2.c_dump].sort
            else
              expr = [x.rhs.rator] + [rhs1.c_dump, rhs2.c_dump]
            end
          else
            expr = [x.rhs.rator] + [rhs1]
          end
          if @expr2val[expr] != nil
            new_val = Ast::AssignStat.new Ast::VarAcc.new(@expr2val[expr].var), Ast::VarAcc.new(x.lhs.var)
            new_val.insert_me "after", x
            puts x.c_dump.chomp + " Reduced to: " + new_val.c_dump
            x.detach_me
            @val2expr[new_val.lhs.c_dump] =  new_val.rhs
          else
            @val2expr[x.lhs.c_dump] = x.rhs
            @expr2val[expr] = x.lhs
          end
        elsif x.rhs.instance_of? Ast::VarAcc
          if @val2rval[x.rhs.c_dump] == nil
            @val2rval[x.lhs.c_dump] = x.rhs
          else
            @val2rval[x.lhs.c_dump] = @val2rval[x.rhs.c_dump]
          end
        end
      end
    end
    def print
      each{|stmt| puts stmt.c_dump}
    end

  end

  class Function
    attr_reader :labels, :entry_bb, :exit_bbs, :val
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
      @cur_bb = BasicBlock.new stmt
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
        fin_bb stmt
      when "Ast::AssignStat"
        @cur_bb << stmt
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

    def initialize func_node
      @labels = Hash.new
      @cur_bb = nil
      @val = func_node
      @exit_bbs = []
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
    funcs.each do |func|
      func.each do |bb|
        bb.process
      end
    end
  end
end
