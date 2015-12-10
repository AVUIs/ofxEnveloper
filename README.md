#ofxEnvRec
ofxEnvRec converts gestures into an envelope type of graphical information, by recognising inflection points from the gesture. Thresholds for horizontal and vertical lines can also be defined. It is particularly aimed for animation and sound applications, and for use with drawing surfaces (such as Wacom tablets or touchscreen interfaces). 

Possible uses:
- audio effect or EQ envelopes;
- animation curves;
- creation/manipulation of audio and/or visual sequences;
- arpeggiators.

Compatibility: openFrameworks 0.9.0

#How it works
Once a gesture is completed, the getEnvelope() method can be executed. 
The getPoints() method can then be used to retrieve the envelope points. 
Gesture and interpolation can be drawn while gesture is executed. 
The clear() method clears the envelope recognition.

#Example
The example-scaling illustrates how a gesture can result in a scaled envelope.
How to run the example:
- Use projectGenerator to create a new project
- Select the addons: ofxEnvRec, ofxMSACore, ofxMSAInterpolator 
- Replace the resulting src folder with the example's src folder

#Credits
Code by Fiore Martin. Examples by Fiore Martin and Nuno Correia.

EnvRec is part of the <a href="http://depic.eecs.qmul.ac.uk">DePIC</a> and <a href="http://avuis.goldsmithsdigital.com">Enabling AVUIs</a> research projects. DePIC is hosted by QMUL and funded by EPSRC. Enabling AVUIs is hosted by Goldsmiths, University of London and funded by the Marie Curie EU fellowship program.

EnvRec relies on Memo Akten’s <a href="http://www.memo.tv/ofxmsainterpolator/">ofxMSAInterpolator</a>.

![ofxEnvRex screenshot](http://www.nunocorreia.com/wp-content/uploads/2015/12/EnvRec.png)

