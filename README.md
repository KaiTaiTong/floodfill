# Flood Fill
This is an implementation of [flood fill] (https://en.wikipedia.org/wiki/Flood_fill) on a PNG image using both breadth-first-search (BFS) and depth-first-search (DFS). 
A point on the image is first selected as our starting point, then a pattern will fill its adjacent regions that share similar color. A demo of borderColorPicker <sup>(1)</sup> and transformColorPicker <sup>(2)</sup> is presented below.













<sup>(1)</sup> borderColorPicker - borders around the edges of regions will be colored, leaving internal pixels unchanged.  <br/>

<sup>(2)</sup> transformColorPicker - patterns from another PNG image get transformed into regions in the current PNG image.
