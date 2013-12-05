Timothy Becker
========================================================================================================================
CSE5095 Computational Geeometry Project, Some Greedy Sampling Hacks and Visualizations
Dealing with Greedy (approximate) Sampling of K-Centers (or Clusters) with a few attempts at the various 
impementations of: Clarkson's:sb(S), Har-Peled's r-nets, and the basic Gonzalez which the others are based on.

Notes:
Files everywhere... Was hacking at various algorithms, gave up, moved on and then created several stiches and bindings
=======================================================================================================================
before retooling some OpenCV bindings to visualize what starts as noise and becomes Vornoi Cells...
=======================================================================================================================


The files you need to run are in the following directory: NN/dist/Release/GNU_4.8-MacOSX
To compile the program you will need GNU-4.8 which has c+11 support
To run the visualization you will need to have 
Python 2.7.6, Numpy, Scipy, and OpenCV2.4.7 with python bindings installed

A python binding Opencv visualizer makes subprocess calls to the greedy_perm app written in C++
passing in the points set and n,k,d values

The c++ app returns the greddy perm indicies of the clusters selected, followed by the asspciation mapping
each point to a particuliar cluster index

Program starts blank, with each press of 'r' you get 10 gaussian points in R^2
upper left screen has number of points n =0 to start, performance, followed by k =1 to start

Visualization Keys:
'w'   -> invert colorspace
'r'   -> get 10 new gaussian points in R^2 visualized in a red-color variant
'2'   -> increase the number of k clusters by 1 starts at 1
'c'   -> toggle cluster visualization (noisy rings with thicker center cluster)
'l'   -> toggle rectangular bound lines from the cluster points to served points
'esc' -> exit visualization

Tested with k <= 25 and n <= 5000 for d = 2 (x,y)
