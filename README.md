# Flood Fill

This is an implementation of [flood fill](https://en.wikipedia.org/wiki/Flood_fill) on a PNG image using both breadth-first-search (BFS) and depth-first-search (DFS). 
A point on the image is first selected as our starting point, then a pattern will fill its adjacent regions that share similar color. A demo of borderColorPicker <sup>(1)</sup> and transformColorPicker <sup>(2)</sup> is presented below.

## Demo

BFS border            |  DFS border
:-------------------------:|:-------------------------:
![bfsborder](https://github.com/KaiTaiTong/floodfill/blob/master/images/demo/bfsborder.gif)  |  ![dfsborder](https://github.com/KaiTaiTong/floodfill/blob/master/images/demo/dfsborder.gif)


BFS transform            |  DFS transform
:-------------------------:|:-------------------------:
![bfstransform](https://github.com/KaiTaiTong/floodfill/blob/master/images/demo/memes_bfs.gif)  |  ![dfstransform](https://github.com/KaiTaiTong/floodfill/blob/master/images/demo/memes_dfs.gif)


<sup>(1)</sup> borderColorPicker - borders around the edges of regions will be colored, leaving internal pixels unchanged.  <br/>
<sup>(2)</sup> transformColorPicker - patterns from another PNG image get transformed into regions in the current PNG image.

## Reference
Skeleton code and structures are provided by [Prof. Cinda K. Heeren](https://www.cs.ubc.ca/people/cinda-heeren) as part of a course on data structure and algorithm in University of British Columbia (UBC).

Raw source images are cited here:<br/>
[pikachu image](https://subiestickers.com/shocked-pikachu/)<br/>
[dog image](https://www.redbubble.com/people/theshirtyurt/works/12670283-doge-very-wow-much-dog-such-shiba-shibe-inu?p=art-print)<br/>
[rainbow image](http://www.aljanh.net/rainbow-spiral-wallpapers/1110593936.html)<br/>


