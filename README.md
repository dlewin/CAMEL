# CAMEL
Creativity Aided Modeling for Electronic Lights

= Project presentation = 

The origins: Where this project came from
In 2006, a project were released as the companion of the 
Beagle Bone Black Server book[http://amzn.com/178439999X]. A dedicated Github repository[http://github.com/dlewin/BeagleboneBlack-Server-Book] were created to be available for anyone who wanted to get introduced to the DIY world. 
Although stable and functional, the code was not intentionally 100\% complete. Some parts were  removed as exercises. 
After a while some readers have requested to improve the code of this project to be a fully functional project. But I wanted something that would bring more functionalities than the version provided with the book. Indeed, even if not so obvious, the code and the book are so related that I was obliged to "restrain" some functionalities to let most of the readers be able to try by themselves. 

⚠
{{color|blue|This is why this project is a complete new design and is no more adapted for newcomers}}

=== The main concepts ===

This whole project will include a designer to create leds figures (AKA patterns), a player to animate these patterns, a client to send patterns to a distant target board connected to a matrix. 
The Player will have 2 versions : as client of the Sender for the network version and as pattern reader who can import saved patterns from a file.
