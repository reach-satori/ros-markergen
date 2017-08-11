# rviz-demoscene

Node that takes in a text file of null-terminated strings and spits out pose messages, 
as well as a python script that generates such paths - currently in only one, a rather stiff kind of movement between random points.
<br><br>
The text file containing the path information contains nothing but the floats for x, y, z
repeating and null characters \0 to separate them. To run the node do you must provide a path to such a file. I realized
halfway through making this that bagfiles already existed, but oh well. I may as well go through with it now.
<br><br>
The node itself is very simple for now. The actual final idea of what I want is a generalized form of creating recursively propagating pose 
messages, such that you'd be able to make really neat looking stuff with nothing but markers and some good equations. The advantage is
that I don't have to depend on ROS for anything: the real programming here is all in the script that will spit out the files describing
the paths.
