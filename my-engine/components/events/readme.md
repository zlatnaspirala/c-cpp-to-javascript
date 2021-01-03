



  Test component scripts: 

  my-engine\components\events\test_html5_mouse.c
  emcc test_html5_mouse.c -O2 -g1 --closure 1 -s DISABLE_DEPRECATED_FIND_EVENT_TARGET_BEHAVIOR=1 -DAUTOMATE_SUCCESS=1  -o test_html5_mouse.html

