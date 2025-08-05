#/bin/bash

a=$(norminette | grep Error | wc -l); if [ $a -eq 0 ]; then echo success\!; else echo error\!; fi
