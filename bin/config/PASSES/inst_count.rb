
# Define a HelloWorld pass
module PassModule

  def new_print counter
    print_call = Ast::Call.new("printf")
    print_call.add_param(Ast::StrConst.new("INST_COUNT:%d"))
    print_call.add_param(new_acc counter)
    print_stat = Ast::AssignStat.new(print_call)
    print_stat
  end
  def new_acc counter
    Ast::VarAcc.new(counter)
  end
  def new_inc counter
    op = Ast::OpExpr.new("+", new_acc(counter), Ast::NumConst.new(1))
    Ast::AssignStat.new(op, new_acc(counter))
  end

  Pass = Proc.new do |prog|
    funcs = prog.children_copy
    counter = Decl::Var.new("counter", Decl::PrimType.get_prim_type("int"))
    prog.add_sym(counter)

    prog.select do |elm|
      elm.is_a?(Ast::Stat) && !(elm.instance_of?(Ast::LabelStat))
    end.each do |stat|
      new_inc(counter).insert_me("before", stat)
    end
    
    main = funcs.find{|func| func.id == "main"}
    main_stats = main.body.children_copy

    Ast::AssignStat.new(Ast::NumConst.new(0), new_acc(counter)).insert_me("after", main_stats[0])
    returns = main_stats.select{|stmt| stmt.instance_of? Ast::ReturnStat}
    returns.each do |ret| 
      new_print(counter).insert_me("before", ret)
    end
    puts main.c_dump
    p prog

  end

end
