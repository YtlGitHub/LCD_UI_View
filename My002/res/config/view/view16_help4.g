{
  "CLASSNAME" : "view",
  "controls" : [ {
    "CLASSNAME" : "image",
    "theme" : "youth",
    "type" : 19,
    "property" : {
      "pub_t" : {
        "name" : "image0",
        "id" : 1,
        "ctrl_type" : 19,
        "pt" : {
          "x" : 133,
          "y" : 440
        },
        "size" : {
          "width" : 536,
          "height" : 152
        },
        "scrollbar_t" : { },
        "alpha" : 255
      },
      "init_img" : "/help/help_4_00.png",
      "rotate_pt" : { }
    }
  }, {
    "CLASSNAME" : "qrcode",
    "theme" : "youth",
    "type" : 21,
    "property" : {
      "pub_t" : {
        "name" : "qrcode0",
        "id" : 3,
        "pt" : {
          "x" : 273,
          "y" : 170
        },
        "size" : {
          "width" : 256,
          "height" : 256
        },
        "scrollbar_t" : { },
        "alpha" : 255
      },
      "bg_color" : 4294967295,
      "color" : 4278190080,
      "txt" : "https://www.baidu.com",
      "width" : 5,
      "border_color" : 4278223103
    }
  }, {
    "CLASSNAME" : "label",
    "theme" : "youth",
    "property" : {
      "pub_t" : {
        "name" : "label0",
        "id" : 2,
        "parent_id" : 1,
        "pt" : {
          "x" : 52,
          "y" : 34
        },
        "size" : {
          "width" : 436,
          "height" : 86
        },
        "scrollbar_t" : { },
        "alpha" : 255
      },
      "dis_mode_e" : 3,
      "animspeed" : 50,
      "align_e" : 2,
      "txt" : "400-888-8888",
      "styles" : [ {
        "name" : "style",
        "txt_t" : {
          "color" : 16777215,
          "font_lib" : "1.ttf",
          "font_size" : 60
        }
      } ]
    }
  } ],
  "view" : {
    "v_name" : "view16_help4",
    "v_id" : 17,
    "bg_color" : 4294967295,
    "bg_image" : "\\background\\Smart_background.png"
  }
}