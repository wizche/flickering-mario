#define LILYGO_WATCH_2020_V1 
#define LILYGO_WATCH_LVGL

#include <LilyGoWatch.h>

LV_IMG_DECLARE(mario);
LV_IMG_DECLARE(world);
LV_IMG_DECLARE(mario_jump);

bool jumping = false;

void setup() {
  Serial.begin(115200);
  TTGOClass *ttgo = TTGOClass::getWatch();
  ttgo->begin();
  ttgo->lvgl_begin();
  ttgo->openBL();

  lv_obj_t *scr = lv_scr_act();
  static lv_style_t style;
  lv_style_init(&style);
  lv_style_set_bg_color(&style, LV_STATE_DEFAULT, LV_COLOR_TRANSP);
  lv_style_set_border_width(&style, LV_STATE_DEFAULT, 0);
  lv_obj_add_style(scr, LV_OBJ_PART_MAIN, &style);

  lv_obj_t *img_bin = lv_img_create(scr, NULL);
  lv_img_set_src(img_bin, &world);
  lv_obj_align(img_bin, NULL, LV_ALIGN_CENTER, 0, 0);
  
  lv_obj_t *marioContainer = lv_cont_create(scr, NULL);
  static lv_style_t cont_style;
  lv_style_init(&cont_style);
  lv_style_set_bg_opa(&cont_style, LV_STATE_DEFAULT, LV_OPA_TRANSP);
  lv_style_set_border_opa(&cont_style, LV_STATE_DEFAULT, LV_OPA_TRANSP);
  lv_obj_add_style(marioContainer, LV_OBJ_PART_MAIN, &cont_style);
  
  lv_obj_set_pos(marioContainer, 100,150);
  lv_obj_set_width(marioContainer, 23);
  lv_obj_set_height(marioContainer, 46);

  lv_obj_t *marioImg = lv_img_create(marioContainer, NULL);
  lv_img_set_src(marioImg, &mario);
  lv_obj_align(marioImg, NULL, LV_ALIGN_CENTER, 0, 0);
  
  lv_task_create(switch_mario, 1000, LV_TASK_PRIO_MID, marioImg);
}

static void switch_mario(struct _lv_task_t *task)
{
  Serial.println("Switching mario image");
  lv_obj_t *marioImg = (lv_obj_t *)task->user_data;
  if(jumping){
    lv_img_set_src(marioImg, &mario);
  } else {
    lv_img_set_src(marioImg, &mario_jump);
  }
  jumping = !jumping;
}

void loop() {
  lv_task_handler();
  delay(5);
}
