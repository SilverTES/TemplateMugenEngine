
def get_title(filename)
  f = File.open(filename, "r")
  str = f.read
  if str =~ /\<title>(.+?)\<\/title\>/
  	return Regexp.last_match(1)
  end
  return ""
end

start = ""

dirname = "refman_work"

puts "Working directory: \n " + start + dirname + "/"

workdir = start + dirname + "/"

fls = Dir.glob(workdir + "*.{html,htm,css}")

puts "Available Files: " + fls.size.to_s

puts "Starting..."

title = get_title(workdir + "index.html")

puts "Title is: " + title

images = Dir.glob(workdir + "images/*.{png, jpg, gif}")

puts "Available Images: " + images.size.to_s

files_string = ""

for f in fls
  files_string += f + "\n"
end

for f in images
  files_string += f + "\n"
end

hhp = File.open("chmproject.hhp", "w")
hhp.write "[OPTIONS]
Auto Index=Yes
Compatibility=1.1 or later
Compiled file=allegro-doc-refman.chm
Contents file=allegro_toc.hhc
Default topic=refman_work\\index.html
Display compile progress=No
Index file=allegro-index
Language=0x409 English (United States)
Title=#{title}


[FILES]
#{files_string}

[INFOTYPES]"

hhp.close

toc_string = ""

for f in fls
  if f.include?(".html") || f.include?(".htm")
  	toc_string += '<LI> <OBJECT type="text/sitemap"><param name="Name" value="' + get_title(f) + '"><param name="Local" value="' + f + '"></OBJECT>' + "\n"
  end
end

puts "Generating TOC..."

toc = File.open("allegro_toc.hhc", "w")
toc.write '<!DOCTYPE HTML PUBLIC "-//IETF//DTD HTML//EN">
<HTML>
<HEAD>
<meta name="GENERATOR" content="Microsoft&reg; HTML Help Workshop 4.1">
<!-- Sitemap 1.0 -->
</HEAD><BODY>
<OBJECT type="text/site properties">
	<param name="Window Styles" value="0x800025">
</OBJECT>
<UL>
	<LI> <OBJECT type="text/sitemap">
		<param name="Name" value="' + title + '">
		</OBJECT>
	<UL>
' + toc_string + '</UL></BODY></HTML>'

@check = /\<div class\=\"searchbox\"\>(.+?)\<div class\=\"content\"\>/mi

puts "Removing Searchbox..."

def remove_searchbox(filename)
  f = File.open(filename, "r")
  str = f.read
  f.close

  str = str.gsub(@check, "</div><div class=\"content\">")

  f = File.open(filename, "w")
  f.write str
  f.close
end

for f in fls
  if f.include?(".html") || f.include?(".htm")
    remove_searchbox(f)
  end
end

puts "Generating index file..."

f = File.open("allegro-index", "w")

f.write '<!DOCTYPE HTML PUBLIC "-//IETF//DTD HTML//EN">
<HTML>
<HEAD>
<meta name="GENERATOR" content="Microsoft&reg; HTML Help Workshop 4.1">
<!-- Sitemap 1.0 -->
</HEAD><BODY>
<UL>
</UL>
</BODY></HTML>'

f.close

puts "Preparation done. Compiling..."