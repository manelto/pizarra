#include <pebble.h>
#include <stdio.h>
#include "idiomas.h"

#define KEY_INVERT 0
#define KEY_IDIOMA 1	
	
// para iniciar el reloj, aunque no haya transcurrido un segundo, la primera vez
bool iniciaHora= true;

// para cambiar el idioma de los literales de meses y días uso un índice
int idioma = 0;
bool inverted = false;

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *pwindow;
static GFont Fuente15;
static GFont Fuente30;
static GFont Fuente50;


static BitmapLayer *BLFondo;
static TextLayer *TLHora;
static TextLayer *TLMinuto;
static TextLayer *TLDiaSem;
static TextLayer *TLDia;
static TextLayer *TLMes;
static TextLayer *TLBateria;
static InverterLayer *ILFondo;

static void in_recv_handler(DictionaryIterator *iterator, void *context)
{
  //Get Tuple
  Tuple *t = dict_read_first(iterator);
  while (t)
  {
    switch(t->key) {
    case KEY_INVERT:
      //It's the KEY_INVERT key
      inverted = (strcmp(t->value->cstring, "si") == 0);
      layer_set_hidden((Layer *)ILFondo, inverted);
 	  persist_write_bool(KEY_INVERT, inverted);
      break;
	  
	case KEY_IDIOMA:
      //It's the KEY_INVERT key
      if(strcmp(t->value->cstring, "1")==0)
      {
        //Set and save as inverted
		idioma=1;  
        persist_write_int(KEY_IDIOMA, 1);
      }
      else if(strcmp(t->value->cstring, "0")==0)
      {
        //Set and save as not inverted
		idioma = 0;
        persist_write_int(KEY_IDIOMA, 0);
      }
      break;
    }
	t = dict_read_next(iterator);
  }
}

static void initialise_ui(void) {
    
  Fuente15 = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_amano_20));
  Fuente30 = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_amano_30));
  Fuente50 = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_amano_40));
 
	
  // BLFondo
  BLFondo = bitmap_layer_create(GRect(0, 0, 144, 168));
  bitmap_layer_set_bitmap(BLFondo, gbitmap_create_with_resource(RESOURCE_ID_pizarra_WHITE));
  //bitmap_layer_set_background_color(BLFondo, GColorWhite);
  layer_add_child(window_get_root_layer(pwindow), (Layer *)BLFondo);
  
  
  // TLHora
  TLHora = text_layer_create(GRect(0, 10, 75, 70));
  text_layer_set_background_color(TLHora, GColorClear);
  text_layer_set_text_color(TLHora, GColorWhite);
  text_layer_set_text(TLHora, "24");
  text_layer_set_text_alignment(TLHora, GTextAlignmentCenter);
  text_layer_set_font(TLHora, Fuente50);
  layer_add_child(window_get_root_layer(pwindow), (Layer *)TLHora);
  
  // TLMinuto
  TLMinuto = text_layer_create(GRect(70, 8, 80, 70));
  text_layer_set_text(TLMinuto, "59");
  text_layer_set_background_color(TLMinuto, GColorClear);
  text_layer_set_text_color(TLMinuto, GColorWhite);
  text_layer_set_text_alignment(TLMinuto, GTextAlignmentCenter);
  text_layer_set_font(TLMinuto, Fuente50);
  layer_add_child(window_get_root_layer(pwindow), (Layer *)TLMinuto);
  
  // TLDiaSem
  TLDiaSem = text_layer_create(GRect(0, 120, 65, 60));
  text_layer_set_background_color(TLDiaSem, GColorClear);
  text_layer_set_text_color(TLDiaSem, GColorWhite);
  text_layer_set_text(TLDiaSem, "ma");
  text_layer_set_text_alignment(TLDiaSem, GTextAlignmentCenter);
  text_layer_set_font(TLDiaSem, Fuente30);
  layer_add_child(window_get_root_layer(pwindow), (Layer *)TLDiaSem);
  
  // TLDia
  TLDia = text_layer_create(GRect(58, 70, 60, 60));
  text_layer_set_background_color(TLDia, GColorClear);
  text_layer_set_text_color(TLDia, GColorWhite);
  text_layer_set_text(TLDia, "30");
  text_layer_set_text_alignment(TLDia, GTextAlignmentCenter);
  text_layer_set_font(TLDia, Fuente30);
  layer_add_child(window_get_root_layer(pwindow), (Layer *)TLDia);
  
  // TLMes
  TLMes = text_layer_create(GRect(50, 110, 90, 52));
  text_layer_set_background_color(TLMes, GColorClear);
  text_layer_set_text_color(TLMes, GColorWhite);
  text_layer_set_text(TLMes, "08");
  text_layer_set_text_alignment(TLMes, GTextAlignmentCenter);
  text_layer_set_font(TLMes, Fuente30);
  layer_add_child(window_get_root_layer(pwindow), (Layer *)TLMes);
  
  
  //ILFondo

  //Comprueba configuración
  inverted = persist_read_bool(KEY_INVERT);
  idioma = persist_read_int(KEY_IDIOMA);
  ILFondo = inverter_layer_create(GRect(0, 0, 144, 168));
  layer_add_child(window_get_root_layer(pwindow), (Layer *)ILFondo);
	
  //Option-specific setup
  if(inverted == true)
  {
     layer_set_hidden((Layer *)ILFondo, false);
  }
  else
  {
     layer_set_hidden((Layer *)ILFondo, true);
  }
  
  
  // TLBateria
  TLBateria = text_layer_create(GRect(115, 70, 40, 30));
  text_layer_set_background_color(TLBateria, GColorClear);
  text_layer_set_text_color(TLBateria, GColorWhite);
  text_layer_set_text(TLBateria, "100");
  text_layer_set_font(TLBateria, Fuente15);
  text_layer_set_text_alignment(TLBateria, GTextAlignmentCenter);
  layer_add_child(window_get_root_layer(pwindow), (Layer *)TLBateria);
	
}

static void sustituye_imagen(GBitmap **imagen, BitmapLayer *bmp_layer, const int resource_id, GPoint origen) {
    GBitmap *vieja_imagen = *imagen;
    *imagen = gbitmap_create_with_resource(resource_id);
    GRect frame = (GRect) {
        .origin = origen,
        .size = (*imagen)->bounds.size
    };
    bitmap_layer_set_bitmap(bmp_layer, *imagen);
    layer_set_frame(bitmap_layer_get_layer(bmp_layer), frame);
    gbitmap_destroy(vieja_imagen);
}


static void destroy_ui(void) {
  window_destroy(pwindow);
  bitmap_layer_destroy(BLFondo);
  text_layer_destroy(TLHora);
  text_layer_destroy(TLMinuto);
  text_layer_destroy(TLDiaSem);
  text_layer_destroy(TLDia);
  text_layer_destroy(TLMes);
  inverter_layer_destroy(ILFondo);
  text_layer_destroy(TLBateria);
}
// END AUTO-GENERATED UI CODE

static void handle_bluetooth(bool connected)
{
	const VibePattern pattern = {
  			.durations = (uint32_t []) {100, 300, 300, 300, 100, 300},
  			.num_segments = 6
	};
	
	if(connected == false)
	{
		//layer_set_hidden((Layer *)ILDesconec, false);
		vibes_enqueue_custom_pattern(pattern);
	} else {
		//layer_set_hidden((Layer *)ILDesconec, true);
		//vibes_enqueue_custom_pattern(pattern);
	}
}

static void handle_battery(BatteryChargeState estado) {
	//GRect frame = layer_get_frame((Layer *) BLBat);
	//GPoint pos = {frame.origin.x, frame.origin.y};
	
	if (estado.is_charging) {
		//sustituye_imagen(&bateria_png, BLBat, RESOURCE_ID_CARGANDO_BLACK, pos);
	} else if (estado.is_plugged) {
		//sustituye_imagen(&bateria_png, BLBat, RESOURCE_ID_CARGANDO_BLACK, pos);
	} else {
		//sustituye_imagen(&bateria_png, BLBat, RESOURCE_ID_BATERIA_BLACK, pos);
	}
	static char buffer_b[] = "100 ";
	snprintf(buffer_b, sizeof(buffer_b), "%d", estado.charge_percent/10);
	text_layer_set_text(TLBateria, buffer_b);	
}

void handle_time(struct tm *tick_time, TimeUnits units_changed)
{
	if (units_changed & MINUTE_UNIT ) {
		// Cambios producidos cada minuto
		static char buffer_min[] = "  ";
		
		strftime(buffer_min,sizeof("00"),"%M",tick_time);
		text_layer_set_text(TLMinuto,buffer_min);
		
		handle_battery(battery_state_service_peek());
	}
	
	if (units_changed & HOUR_UNIT  || iniciaHora) {
    	iniciaHora = false;
		static char buffer_dia[] = "  ";
		static char buffer_hora[] = "  ";
		static char buffer_mes[] = "  ";
		
		static char txt_dia[] = "dom ";
		//static char txt_mes[] = "ene ";  
		int dia = tick_time->tm_wday;
		//int mes = tick_time->tm_mon;
    	strftime(buffer_hora,sizeof("00"),"%k",tick_time);
		text_layer_set_text(TLHora,buffer_hora);
		strncpy(txt_dia, dias[7*idioma+dia], sizeof(dias[7*idioma+dia]));
		text_layer_set_text(TLDiaSem, txt_dia);
		
		strftime(buffer_mes,sizeof("00"),"%m",tick_time);
		text_layer_set_text(TLMes,buffer_mes);

		strftime(buffer_dia,sizeof("00"),"%e",tick_time);
		text_layer_set_text(TLDia,buffer_dia);
     }
}

void window_load(Window *window)
{
	initialise_ui();
	//Para la primera vez, lanzo manualmente la actualización del reloj y bluetooth
	time_t temp = time(NULL);
	handle_time(localtime(&temp), MINUTE_UNIT);
	handle_battery(battery_state_service_peek());
	handle_bluetooth(bluetooth_connection_service_peek());
}

void window_unload(Window* window) {
  	destroy_ui();
}

void init() {
	
	tick_timer_service_subscribe(MINUTE_UNIT, &handle_time);
	bluetooth_connection_service_subscribe(&handle_bluetooth);
	battery_state_service_subscribe(&handle_battery);
	app_message_register_inbox_received((AppMessageInboxReceived) in_recv_handler);
	app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());
	
	pwindow = window_create();
	//window_set_click_config_provider(pwindow, click_config_provider);
	
	window_set_window_handlers(pwindow, (WindowHandlers) {
		.load = window_load,
		.unload = window_unload,
	});

	window_stack_push(pwindow,true);
}	

void deinit() {
	tick_timer_service_unsubscribe();
	bluetooth_connection_service_unsubscribe();
	battery_state_service_unsubscribe();
}

int main(void) {
    init();
    app_event_loop();
	deinit();
}