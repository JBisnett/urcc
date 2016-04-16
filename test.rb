#!/usr/bin/ruby

module Execute
  def execute( cmd )
    puts "#{cmd}"
    res = `#{cmd}`
    return res
  end
end

class Tester
  include Execute
  def initialize( args )
    get_test_dir

    files = check_file_arg( args[0] )
    if(args.size > 1)
      check_urcc_arg( args[1] )
    else
      @urcc = 'urcc'
    end


    @report = "urcc_test_results.txt"
    execute("\\rm -f #{@report}") if File.file?(@report)

    @tests = Array.new

    files.each{ |f|
      @tests << Test.new( @test_dir, File.basename(f), @urcc, @report )
    }
  end

  def test
    @tests.each{ |t| t.test }
    puts "Testing finished.  The results are in #{Dir.getwd}/#{@report}.\n\n"
    if @tests.size > 1
      res = execute("egrep -i \"CS255 Test|counter=\" #{Dir.getwd}/#{@report}")
      puts res
      puts "You may submit the above output as the result of the project."
    end 
  end

  def get_root_dir
    found = false
    file = '.git'
    while not File.exist?(file) and File.directory?(File.dirname(file))
      file = '../' + file
    end
    if not File.exist?( file ) 
      abort("Abort: can't find the git repository root in parent directories")
    end
    return File.dirname(File.expand_path( file ) )
  end

  def get_test_dir
    root = get_root_dir
    @test_dir = "tests"
  end

  def check_file_arg( arg )
    all = Dir.glob(File.join(@test_dir,"*.c"))
    #all.delete(".")
    #all.delete("..")
    return all if ( arg.downcase == 'all' )
    
    file = File.basename(arg, ".c")
    if not File.exists?( File.join(@test_dir,"#{file}.c"))
      abort("Test program #{file}.c not found.  Choose one of the following: #{all * ', '}")
    end
    return ["#{file}.c"]
  end

  def check_urcc_arg( arg )
    abort( "#{arg} does not exist (or it is not an executable)" ) if not (File.exists?(arg) and File.executable?(arg))
    @urcc = arg
  end
end

class Test
  include Execute

  def initialize( dir, prog, urcc, report )
    @dir, @prog, @urcc, @report = dir, prog, urcc, report
    @params = Hash.new
    @params[ "automaton.c" ] = "1 0 0 1 0 0 -1"
    @params[ "binrep.c" ] = "255"
    @params[ "movingedge.c" ] = "455 42"
    @params[ "multiply.c" ] = "1000 50"
    @params[ "tax.c" ] = "20000 200 20 0 1 2100 0"
    @params[ "trivia.c" ] = "20"
    @params[ "odd.c" ] = "255"
  end

  def test
    puts "testing #{@prog} ..."
    tmp = "tmp_#{@prog}"
    execute("echo \"#include <stdio.h>\n\" > #{tmp}")
    extra = ""
    # uncomment the following two lines to test the 255 compiler
    #execute("echo \"#include <cs255-lib.h>\n\" >> #{tmp}")
    #extra = "-fcs255 -I#{@dir}/../1_/base/ #{@dir}/../1_gcc/base/cs255-lib.c"
    execute("cat #{@dir}/#{@prog} >> #{tmp}")
    execute("#{@urcc}  #{tmp} #{extra}")
    execute("echo \"CS255 Test (#{Time.now}): #{@prog}\" >> #{@report}")
    tmp_base = File.basename(tmp,'.c')
    tmp_exe = tmp_base+".bin"
    if @params[ @prog ] != nil
      execute("echo \"#{@params[@prog]}\" | ./#{tmp_exe} >> #{@report}")
    else
      execute("./#{tmp_exe} >> #{@report}")
    end
    File.delete(tmp_exe)
    File.delete(tmp_base+'.ll')
    File.delete(tmp_base+'_urcc_opt.c')
    File.delete(tmp)
  end
end

if ARGV.size != 1
  abort("\tUsage: test.rb [all | prog_name ] \tExplanations: 'prog_name' is a test in projects/test_cases. Use 'all' to test all .c files in the directory with standard inputs.")  
# You will be asked whether to submit the results.  New results may be submitted to replce the previous submission.")
end

tester = Tester.new( ARGV )
tester.test
