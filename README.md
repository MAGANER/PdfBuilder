# PdfBuilder
markdown-like language to generate pdf documents.

# The reason to be created
As you can know the pdf was created as portable format of textual information.<br>
So i prefer to share some documents with ```.pdf``` format instead of ```.txt```, ```.doc```, ```.docx``` e.t.c<br>
But every .doc/.docx editors are very clumsy in my opinion. So i was inspired by ```LaTex``` to<br>
create language to generate pdf generators, because i prefer Emacs above all else.

Current state of language is very minimalistic, but it is able to create simple documents.

# How to use
pdfbuilder.exe ```-sscriptname``` ```-doutput``` ```-mmacrofile```<br>
macrofile is optional.<br>

# Syntax
There are 2 elements: regular text and tags, changing rendering state.<br>
Every tag is surrounded with <>, so it looks like ```<tag>```<br>
Also it can have arguments, so it will look like ```<tag:arg1,argn>```<br>

So check list of tag below:<br>

```<br>``` - moves the cursor down to the start of new line.<br>
```<rs>``` - resets state of rendering, setting the default values.<br>
```<hr>``` - sets horizontal line at current place of cursor.(i mean current position along Y axis).<br>
```<np>``` - creates new page.
```<ss:arg>```  - takes any natural number and sets spaces.<br>
```<str:arg>``` - takes any number and sets text rise.<br>
```<fs:arg>```  - takes any natural number and sets the size of font.<br>  
```<fc:red,green,blue>``` - takes 3 number beetween 0 and 255 and sets the color in RGB-space.<br>
```<img:path>``` - takes the path of image and sets it at current position of cursor<br>
```<rt:angle>``` - takes the angle between 0 and 360 and sets rotation angle of every object on page.<br>
```<mx:arg>``` - takes number between 0% and 100% and moves position from right side to left one along X axis.<br>
```<my:arg>``` - takes number between 0% and 100% and moves position from right side to left one along Y axis.<br>
```<sk:arg>``` - takes real number as a value of kerning.

## Macro
Macro acts in the same way like ```DEFINE``` from C/C++ programming language. It is used to replace complex anything.<br>
to define macro write - ```<mac:name#value>``` <br>
to use macro write anywhere you need ```@name```, so macro value will be put instead of ```@name```

### Macro file
Just a regular file, containg a list of predefined macroses.<br>
Before your script is loaded and processed, it reads the macro script and saves all macroses and then<br>
they can be used in your script<br>
