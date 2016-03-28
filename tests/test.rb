#!/usr/bin/ruby
`rake`
ARGV.each do |file|
    name = file.split(".")[0]
    `urcc #{file}`
    File.write(name+".def", File.read("defs.out"))
end
