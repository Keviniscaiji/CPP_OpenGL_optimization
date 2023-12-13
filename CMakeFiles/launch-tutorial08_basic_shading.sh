#!/bin/sh
bindir=$(pwd)
cd /Users/gongkaiwen/Desktop/研究生/第一学期/ece 6122/ogl-master 2/tutorial08_basic_shading/
export 

if test "x$1" = "x--debugger"; then
	shift
	if test "x" = "xYES"; then
		echo "r  " > $bindir/gdbscript
		echo "bt" >> $bindir/gdbscript
		GDB_COMMAND-NOTFOUND -batch -command=$bindir/gdbscript  /Users/gongkaiwen/Desktop/研究生/第一学期/ece\ 6122/ogl-master\ 2/tutorial09_vbo_indexing/tutorial08_basic_shading 
	else
		"/Users/gongkaiwen/Desktop/研究生/第一学期/ece\ 6122/ogl-master\ 2/tutorial09_vbo_indexing/tutorial08_basic_shading"  
	fi
else
	"/Users/gongkaiwen/Desktop/研究生/第一学期/ece\ 6122/ogl-master\ 2/tutorial09_vbo_indexing/tutorial08_basic_shading"  
fi
