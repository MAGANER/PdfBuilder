# PdfBuilder
markdown-like language to generate pdf documents.

# The reason to be created
As you can know the pdf was created as portable format of textual information.<br>
So i prefer to share some documents with ```.pdf``` format instead of ```.txt```, ```.doc```, ```.docx``` e.t.c<br>
But every .doc/.docx editors are very clumsy in my opinion. So i was inspired by ```LaTex``` to<br>
create language to generate pdf generators, because i prefer Emacs above all else.

Current state of language is very minimalistic, but it is able to create simple documents.

# Syntax
There are 2 elements: regular text and tags, changing rendering state.<br>
Every tag is surrounded with <>, so it looks like ```<tag>```<br>
Also it can have arguments, so it will look like ```<tag:arg1,argn>```<br>

So check list of tag below:<br>

```<br>``` - moves the cursor down to the start of new line.<br>
```<rs>``` - resets state of rendering, setting the default values.<br>
```<hr>``` - sets horizontal line at current place of cursor.(i mean current position along Y axis).<br>
```<ss:arg>```  - takes any natural number and sets spaces.<br>
```<str:arg>``` - takes any number and sets text rise.<br>
```<fs:arg>```  - takes any natural number and sets the size of font.<br>  
```<fc:red,green,blue>``` - takes 3 number beetween 0 and 255 and sets the color in RGB-space.<br>
```<img:path>``` - takes the path of image and sets it at current position of cursor<br>
```<rt:angle>``` - takes the angle between 0 and 360 and sets rotation angle of every object on page.<br>
