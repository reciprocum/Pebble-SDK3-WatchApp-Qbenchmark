#include <Config.h>
#include <pebble.h>
#include <Q.h>

Window    *my_window ;
TextLayer *text_layer ;

#define LOOP_COUNT  1000000000


void
run_benchmark( void )
{
  // native floats.
  float e  = 2.71828182845904523536028747135f ;
  float pi = 3.14159265358979323846264338323f ;
  float c ;

  static uint16_t beforeMs, afterMs ;
  time_ms( NULL, &beforeMs ) ;
  LOGD( "float.beforeMs := %d", beforeMs ) ;
  
  for (int i = 0  ;  i < LOOP_COUNT  ;  ++i)
    c = e * pi ;

  time_ms( NULL, &afterMs ) ;
  LOGD( "float.afterMs := %d", afterMs ) ;
  
  c += 1.0 ;  // Dummy just to mute the "unused variable" compiler warning/error.

  LOGD( "float.elapsed (count = %d) := %d", LOOP_COUNT, (int)(afterMs - beforeMs) ) ;
  
  
  // Q15.16 floats.
  Q qE  = Q_E ;
  Q qPi = Q_PI ;
  Q qC ;

  time_ms( NULL, &beforeMs ) ;
  LOGD( "Q.beforeMs := %d", beforeMs ) ;

  for (int i = 0  ;  i < LOOP_COUNT  ;  ++i)
    qC = Q_mul( qE, qPi ) ;

  time_ms( NULL, &afterMs ) ;
  LOGD( "Q.afterMs := %d", afterMs ) ;

  qC = Q_add( qC, Q_1 ) ;  // Dummy just to mute the "unused variable" compiler warning/error.

  LOGD( "Q.elapsed (count = %d) := %d", LOOP_COUNT, (int)(afterMs - beforeMs) ) ;
}


void
handle_init(void)
{
  my_window = window_create();

  text_layer = text_layer_create(GRect(0, 0, 144, 20));
  window_stack_push(my_window, true);
}

void
handle_deinit(void)
{
  text_layer_destroy(text_layer) ;
  window_destroy(my_window) ;
}

int
main( void )
{
  handle_init( ) ;
  run_benchmark( ) ;
  app_event_loop( ) ;
  handle_deinit( ) ;
}