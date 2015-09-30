# passNotes
An extremely basic chat program for users logged into the same Linux system. 

I can't imagine this being useful except in the specific scenario in which it was conceived; programming students trying to chat, in-lab, via the Linux server we are all connected to. In our environment, each user is alloted only 50 MBs and no sudoer privilege, so installing IRC clients by compiling from source was not an option. The built-in "talk" command muddles text as people write over each other, and includes no identifying information re: who is writing what. Hence, this tiny chat client/server.

More importantly, this is an excuse for me to learn C socket programming and pthreads.
