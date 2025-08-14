README
zirconpaint
painting tool designed for a uni project, currently in prototype stage. 
This version is not packaged properly and I only intend for it to be my submission copy if I fail to submit anything else after the deadline/able to do a resub, just showing what I have on the deadline.

It doesn't compile due to an issue with copying certain SFML functions in the Buttons class. It will run if the RenderTexture "ButtonColouredTexture" inside the button class (and associated calls) are commented out.
I do not know why I cannot copy a rendertexture inside a class, even calling the class with a reference doesn't fix it, and I am at a loss of how to implement it. I've handled it with pointers before, but I feel there is a simpler method which I would like to try to implement. If I don't try to copy it, the program crashes. on startup and provides no information why. Nothing gets printed to the console. There is just a breakpoint exception called at the very end of the program with no info. I am very tired and as a rule I will not continue to program after my psych meds have worn off.


You can change colours with the number keys, because currently the buttons don't quite work
you can also undo with ctrl+z
left control only
not resizable, it must be in 720p window for the moment.

Version 0.2.1.1

Changelog:
Version 0.2.1.1 (Unstable):
	Attempted to add colour buttons - doesn't work seemingly due to an issue within SFML.

Version 0.2.1: 
	Added stamp tool button

Version 0.2.0:
	Added Stamp Tool

Version 0.1.2:
	Added buttons to select tools.

Version 0.1.1:
	Undo feature no longer crashes the program when you press ctrl+z when no items are present on screen.

Version 0.1.0:
	Line tool no longer scales from 0,0 coordinates. 
	Added lines to interpolate into the freehand tool so it looks smoother.
	Added undo feature.

Known Bugs:
	sometimes a flickering circle appears before the start of a freehand line if the user draws one extremely quickly immediately after selecting the tool.

