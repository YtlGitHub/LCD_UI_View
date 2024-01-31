{
  "CLASSNAME" : "view",
  "controls" : [ {
    "CLASSNAME" : "label",
    "theme" : "youth",
    "property" : {
      "pub_t" : {
        "name" : "label0",
        "id" : 6,
        "pt" : {
          "x" : 75,
          "y" : 540
        },
        "size" : {
          "width" : 660,
          "height" : 70
        },
        "scrollbar_t" : { },
        "hidden" : true,
        "alpha" : 255
      },
      "dis_mode_e" : 3,
      "animspeed" : 50,
      "align_e" : 2,
      "txt" : "#current_battery_level_low",
      "styles" : [ {
        "name" : "style",
        "txt_t" : {
          "color" : 16777215,
          "font_lib" : "1.ttf",
          "font_size" : 40
        }
      } ]
    }
  }, {
    "CLASSNAME" : "image",
    "theme" : "youth",
    "type" : 19,
    "property" : {
      "pub_t" : {
        "name" : "image3",
        "id" : 4,
        "ctrl_type" : 19,
        "pt" : {
          "x" : 551,
          "y" : 295
        },
        "size" : {
          "width" : 47,
          "height" : 47
        },
        "scrollbar_t" : { },
        "alpha" : 255
      },
      "init_img" : "\\charging\\number_big_white_%.png",
      "rotate_pt" : { }
    }
  }, {
    "CLASSNAME" : "image",
    "theme" : "youth",
    "type" : 19,
    "property" : {
      "pub_t" : {
        "name" : "image4",
        "id" : 5,
        "ctrl_type" : 19,
        "pt" : {
          "x" : 195,
          "y" : 230
        },
        "size" : {
          "width" : 46,
          "height" : 94
        },
        "scrollbar_t" : { },
        "alpha" : 255
      },
      "init_img" : "\\charging\\chong_icon_dian0.png",
      "rotate_pt" : { }
    }
  }, {
    "CLASSNAME" : "label",
    "theme" : "youth",
    "property" : {
      "pub_t" : {
        "name" : "label1",
        "id" : 7,
        "pt" : {
          "x" : 185,
          "y" : 140
        },
        "size" : {
          "width" : 421,
          "height" : 186
        },
        "scrollbar_t" : { },
        "alpha" : 255
      },
      "animspeed" : 50,
      "align_e" : 2,
      "txt" : "100",
      "styles" : [ {
        "name" : "style",
        "body_t" : {
          "padding" : {
            "top" : 2147483647,
            "bottom" : 2147483647,
            "left" : 2147483647,
            "right" : 2147483647,
            "inner" : 2147483647
          }
        },
        "txt_t" : {
          "color" : 16777215,
          "font_lib" : "1.ttf",
          "font_size" : 190
        }
      } ]
    }
  } ],
  "view" : {
    "v_name" : "view08_charging",
    "v_id" : 8,
    "bg_color" : 4278190080,
    "bg_image" : "/charging/red_01.png"
  }
}