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
          "x" : 200,
          "y" : 40
        },
        "size" : {
          "width" : 400,
          "height" : 500
        },
        "scrollbar_t" : { },
        "alpha" : 255
      },
      "init_img" : "\\help\\help_1_00.png",
      "rotate_pt" : { }
    }
  }, {
    "CLASSNAME" : "image",
    "theme" : "youth",
    "type" : 19,
    "property" : {
      "pub_t" : {
        "name" : "image1",
        "id" : 2,
        "ctrl_type" : 19,
        "pt" : {
          "x" : 217,
          "y" : 440
        },
        "size" : {
          "width" : 367,
          "height" : 103
        },
        "scrollbar_t" : { },
        "alpha" : 255
      },
      "init_img" : "\\fault\\0_00.png",
      "rotate_pt" : { }
    }
  }, {
    "CLASSNAME" : "label",
    "theme" : "youth",
    "property" : {
      "pub_t" : {
        "name" : "label0",
        "id" : 3,
        "pt" : {
          "x" : 300,
          "y" : 515
        },
        "size" : {
          "width" : 300,
          "height" : 50
        },
        "scrollbar_t" : { },
        "alpha" : 255
      },
      "dis_mode_e" : 3,
      "animspeed" : 50,
      "align_e" : 1,
      "txt" : "#quick_guide",
      "styles" : [ {
        "name" : "style",
        "txt_t" : {
          "color" : 16777215,
          "font_lib" : "1.ttf",
          "font_size" : 50
        }
      } ]
    }
  }, {
    "CLASSNAME" : "label",
    "theme" : "youth",
    "property" : {
      "pub_t" : {
        "name" : "label1",
        "id" : 4,
        "pt" : {
          "x" : 200,
          "y" : 525
        },
        "size" : {
          "width" : 100,
          "height" : 50
        },
        "scrollbar_t" : { },
        "alpha" : 255
      },
      "animspeed" : 50,
      "align_e" : 3,
      "txt" : "1/4",
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
          "color" : 33023,
          "font_lib" : "1.ttf",
          "font_size" : 50
        }
      } ]
    }
  }, {
    "CLASSNAME" : "qrcode",
    "theme" : "youth",
    "type" : 21,
    "property" : {
      "pub_t" : {
        "name" : "qrcode0",
        "id" : 5,
        "pt" : {
          "x" : 273,
          "y" : 220
        },
        "size" : {
          "width" : 256,
          "height" : 256
        },
        "scrollbar_t" : { },
        "hidden" : true,
        "alpha" : 255
      },
      "bg_color" : 4294967295,
      "color" : 4278190080,
      "txt" : "https://www.baidu.com",
      "width" : 5,
      "border_color" : 4278223103
    }
  } ],
  "view" : {
    "v_name" : "view12_help",
    "v_id" : 13,
    "bg_color" : 4294967295,
    "bg_image" : "/background/home_menu_basebg00.png"
  }
}