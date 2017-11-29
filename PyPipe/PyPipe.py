import io
import os
mypipe = "/pipes/mypipe"

pipe_fd = open(mypipe)
if pipe_fd is not -1:
	msg = pipe_fd.read()
	print(msg)
exit()
