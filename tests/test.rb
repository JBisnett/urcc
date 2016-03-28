#!/usr/bin/ruby
`rake`
ARGV.each do |file|
    name = file.split(".")[0]
    `urcc #{file}`
    File.write(name+".urcc_def_use", File.read("defs.out"))
end
