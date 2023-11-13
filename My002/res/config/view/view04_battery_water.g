{
  "CLASSNAME" : "view",
  "controls" : [ {
    "CLASSNAME" : "arc",
    "theme" : "youth",
    "type" : 5,
    "property" : {
      "pub_t" : {
        "name" : "arc0",
        "id" : 1,
        "ctrl_type" : 5,
        "pt" : {
          "x" : 20,
          "y" : 20
        },
        "size" : {
          "width" : 760,
          "height" : 760
        },
        "scrollbar_t" : { },
        "alpha" : 255
      },
      "angle_t" : {
        "start_angle" : 45,
        "end_angle" : 315
      },
      "range_t" : {
        "maxvalue" : 100
      },
      "know_dis_en" : true,
      "arc_t_main" : {
        "color" : 4278223103,
        "width" : 10,
        "opa" : 255
      },
      "arc_t_inc" : {
        "color" : 4294901760,
        "width" : 10,
        "opa" : 255
      },
      "styles" : [ {
        "style_part" : 196608,
        "name" : "knob_style",
        "body_t" : {
          "main_color" : 16711680,
          "grad_color" : 16711680,
          "radius" : -1
        },
        "txt_t" : { }
      } ]
    }
  }, {
    "CLASSNAME" : "image",
    "theme" : "youth",
    "type" : 19,
    "property" : {
      "pub_t" : {
        "name" : "image0",
        "id" : 2,
        "ctrl_type" : 19,
        "pt" : {
          "x" : 95,
          "y" : 320
        },
        "size" : {
          "width" : 60,
          "height" : 130
        },
        "scrollbar_t" : {
          "mode_e" : 1
        },
        "alpha" : 255
      },
      "init_img" : "/battery_water/battery00.png",
      "rotate_pt" : { }
    }
  }, {
    "CLASSNAME" : "image",
    "theme" : "youth",
    "type" : 19,
    "property" : {
      "pub_t" : {
        "name" : "image1",
        "id" : 3,
        "ctrl_type" : 19,
        "pt" : {
          "x" : 640,
          "y" : 320
        },
        "size" : {
          "width" : 60,
          "height" : 130
        },
        "scrollbar_t" : { },
        "alpha" : 255
      },
      "init_img" : "\\battery_water\\water (1).png",
      "rotate_pt" : { }
    }
  }, {
    "CLASSNAME" : "label",
    "theme" : "youth",
    "property" : {
      "pub_t" : {
        "name" : "label0",
        "id" : 4,
        "pt" : {
          "x" : 60,
          "y" : 450
        },
        "size" : {
          "width" : 120,
          "height" : 56
        },
        "scrollbar_t" : { },
        "alpha" : 255
      },
      "dis_mode_e" : 3,
      "animspeed" : 50,
      "align_e" : 2,
      "txt" : "0%",
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
          "font_size" : 40
        }
      } ]
    }
  }, {
    "CLASSNAME" : "label",
    "theme" : "youth",
    "property" : {
      "pub_t" : {
        "name" : "label2",
        "id" : 6,
        "pt" : {
          "x" : 590,
          "y" : 450
        },
        "size" : {
          "width" : 161,
          "height" : 56
        },
        "scrollbar_t" : { },
        "alpha" : 255
      },
      "dis_mode_e" : 3,
      "animspeed" : 50,
      "align_e" : 2,
      "txt" : "#water",
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
          "font_size" : 40
        }
      } ]
    }
  } ],
  "view" : {
    "v_name" : "view04_battery_water",
    "v_id" : 4,
    "bg_color" : 4282384448,
    "layer" : 1
  }
}