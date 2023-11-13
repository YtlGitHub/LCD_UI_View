#ifndef __GRF_CTRL_I_H_
#define __GRF_CTRL_I_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "grf_typedef.h"
#include "grf_view_i.h"

typedef void  grf_ctrl_t;

/********************************public struct**************************************************/
typedef enum 
{
    GRF_TOUCH_NONE,              //禁止触摸
    GRF_TOUCH_CLICK,             //可以点击
}grf_touch_mode_e;
typedef enum 
{
    GRF_SCROLL_NONE,                     // 不做处理
    GRF_SCROLL_LEFT_TOP,                // 滚动后垂直方向置顶，水平方向靠左
    GRF_SCROLL_RIGHT_BOTTOM,             //滚动后垂直方向靠底，水平方向靠右
    GRF_SCROLL_CENTER,                  //滚动后居中
} grf_scroll_dir_e;

typedef enum {
    GRF_STATE_DEFAULT     =  0x0000,         //正常状态
    GRF_STATE_CHECKED     =  0x0001,         //切换或者选中
    GRF_STATE_FOCUSED     =  0x0002,         //点击
    GRF_STATE_FOCUS_KEY   =  0x0004,         //聚焦
    GRF_STATE_EDITED      =  0x0008,         //编辑
    GRF_STATE_PRESSED     =  0x0020,         //已按下
    GRF_STATE_SCROLLED    =  0x0040,         //滚动状态
    GRF_STATE_DISABLED    =  0x0080,         //禁用
}grf_obj_state_e;
typedef enum 
{
    GRF_DROP_DIR_NONE     = 0x00,
    GRF_DROP_DIR_LEFT     = 0x01,        //向左展开
    GRF_DROP_DIR_RIGHT    = 0x02,        //向右展开
    GRF_DROP_DIR_TOP      = 0x04,        //向上展开
    GRF_DROP_DIR_BOTTOM   = 0x08,        //向下展开
}grf_droplist_dir_e;
typedef enum 
{
    GRF_ALIGN_DEFAULT = 0,
    GRF_ALIGN_IN_TOP_LEFT,                  // 在控件内部顶端靠左对齐
    GRF_ALIGN_IN_TOP_MID,                   // 在控件内部顶端中间对齐
    GRF_ALIGN_IN_TOP_RIGHT,                 // 在控件内部顶端靠右对齐
    GRF_ALIGN_IN_BOTTOM_LEFT,               // 在控件内部底端靠左对齐
    GRF_ALIGN_IN_BOTTOM_MID,                // 在控件内部底端靠间对齐
    GRF_ALIGN_IN_BOTTOM_RIGHT,              // 在控件内部底端靠右对齐
    GRF_ALIGN_IN_LEFT_MID,                  // 在控件内部靠左居中对齐
    GRF_ALIGN_IN_RIGHT_MID,                 // 在控件内部靠右居中对齐
    GRF_ALIGN_CENTER ,                      // 居中对齐
    GRF_ALIGN_OUT_TOP_LEFT,                 // 在控件外部顶端靠左对齐
    GRF_ALIGN_OUT_TOP_MID,                  // 在控件外部顶端中间对齐
    GRF_ALIGN_OUT_TOP_RIGHT,                // 在控件外部顶端靠右对齐
    GRF_ALIGN_OUT_BOTTOM_LEFT,              // 在控件外部底端靠左对齐
    GRF_ALIGN_OUT_BOTTOM_MID,               // 在控件外部底端靠间对齐
    GRF_ALIGN_OUT_BOTTOM_RIGHT,             // 在控件外部底端靠右对齐
    GRF_ALIGN_OUT_LEFT_TOP,                 // 在控件外部靠左顶部对齐
    GRF_ALIGN_OUT_LEFT_MID,                 // 在控件外部靠左居中对齐
    GRF_ALIGN_OUT_LEFT_BOTTOM,              // 在控件外部靠左底部对齐
    GRF_ALIGN_OUT_RIGHT_TOP,                // 在控件外部靠右顶部对齐
    GRF_ALIGN_OUT_RIGHT_MID,                // 在控件外部靠右居中对齐
    GRF_ALIGN_OUT_RIGHT_BOTTOM,             // 在控件外部靠右底部对齐
                                           
}grf_align_e;
//根据编号获取控件
grf_ctrl_t* grf_ctrl_get_form_id(u32 view_id,u32 ctrl_id);   
//显示控件 ,如果控件被删除,将重新创建,如果控件被隐藏,将显示出来
grf_ctrl_t* grf_ctrl_show(u32 view_id,u32 ctrl_id);
//设置控件显示位置
s32 grf_ctrl_set_pos(grf_ctrl_t* ctrl_t,grf_coord_t x,grf_coord_t y);  
//设置控件大小
s32 grf_ctrl_set_size(grf_ctrl_t* ctrl_t,grf_coord_t w,grf_coord_t h); 
//设置是否隐藏
s32 grf_ctrl_set_hidden(grf_ctrl_t* ctrl_t,grf_bool hidden);       
//设置透明度
s32 grf_ctrl_set_alpha(grf_ctrl_t* ctrl_t,u8 scale);       
//设置点击模式
s32 grf_ctrl_set_touch(grf_ctrl_t* ctrl_t,grf_touch_mode_e t_mode);   
//设置 扩大控件触摸点击范围
s32 grf_ctrl_set_ext_click_area(grf_ctrl_t* ctrl_t,grf_coord_t size);    
//设置控件之间的相对位置
s32 grf_ctrl_set_align(grf_ctrl_t* ctrl_t,grf_ctrl_t* base_ctrl,grf_align_e align,grf_coord_t x_offset,grf_coord_t y_offset); 
//设置控件前置
s32 grf_ctrl_move_forground(grf_ctrl_t* ctrl_t);     
//设置控件后置
s32 grf_ctrl_move_background(grf_ctrl_t* ctrl_t);    
//获取控件的子控件数量
u32 grf_ctrl_get_child_sum(grf_ctrl_t* ctrl_t);
//获取控件的指定子控件
grf_ctrl_t *grf_ctrl_get_child(grf_ctrl_t* ctrl_t,u32 child_id);
//获取控件所在区域
s32 grf_ctrl_get_coords(grf_ctrl_t* ctrl_t,grf_area_t *grf_coords); 
//设置控件滚动后子对象对齐位置（垂直方向）
s32 grf_ctrl_set_scroll_dir_y(grf_ctrl_t* ctrl_t,grf_scroll_dir_e scroll_dir);
//设置控件滚动后子对象对齐位置（水平方向）
s32 grf_ctrl_set_scroll_dir_x(grf_ctrl_t* ctrl_t,grf_scroll_dir_e scroll_dir);
//将子控件滚动到父控件可见位置（具体位置可由grf_scroll_dir_e设置）
s32 grf_ctrl_scroll_view(grf_ctrl_t* ctrl_t,grf_bool anim);
//当父控件滚动时此控件不滚动
s32 grf_ctrl_child_not_scroll(grf_ctrl_t* ctrl_t);
//当父控件滚动时判断该子控件是否同步滚动
grf_bool grf_ctrl_child_get_scroll(grf_ctrl_t* ctrl_t);
//获取对象y坐标
u32 grf_ctrl_get_y(grf_ctrl_t* ctrl_t);
//获取对象x坐标
u32 grf_ctrl_get_x(grf_ctrl_t* ctrl_t);
//刷新控件位置
s32 grf_ctrl_update_location(grf_ctrl_t* ctrl_t);
//改变控件x坐标（默认状态）
s32 grf_ctrl_translate_x(grf_ctrl_t* ctrl_t,grf_coord_t x);
//计算算术平方根(输入x(正数)，输出res)
s32 grf_square_root(u32 x,grf_sqrt_t *res);
//根据x值匹配输入与输出值映射,输出x对应的值
u32 grf_map_relation(u32 x,u32 min_in,u32 max_in,u32 min_out,u32 max_out);
//设置控件缩放（128一半，256正常，512一倍）(默认状态)
s32 grf_ctrl_zoom_set(grf_ctrl_t* ctrl_t,u32 num);
//设置控件缩放中心(默认状态)
s32 grf_ctrl_zoom_pivot(grf_ctrl_t* ctrl_t,u32 x,u32 y);
/*********************************event 事件************************************/
typedef enum {
    GRF_EVENT_ALL = 0,
    GRF_EVENT_PRESSED,                          //控件按下
    GRF_EVENT_PRESSING,                         //控件按下连续发送事件
    GRF_EVENT_PRESS_LOST,                       //控件触摸丢失,触控划出控件时
    GRF_EVENT_SHORT_CLICKED,                    //控件触摸点击,短时间按下
    GRF_EVENT_LONG_PRESSED,                     //控件触摸长按达到一定时间后发送一次
    GRF_EVENT_LONG_PRESSED_REPEAT,              //控件触摸长按达到一定时间后连续发送
    GRF_EVENT_CLICKED,                          //控件触摸抬起,
    GRF_EVENT_RELEASED,                         //控件触摸释放
    GRF_EVENT_SCROLL_BEGIN,                     //控件滚动开始
    GRF_EVENT_SCROLL_END,                       //控件滚动结束
    GRF_EVENT_SCROLL,                           //检测到滚动
    GRF_EVENT_GESTURE,                          //检测到手势
    GRF_EVENT_KEY,                              //控件键盘事件
    GRF_EVENT_FOCUSED,                          //控件获得焦点
    GRF_EVENT_DEFOCUSED,                        //控件释放焦点
	GRF_EVENT_LEAVE,							//控件不是焦点,但是被选中

    GRF_EVENT_VALUE_CHANGED=28,                 //控件值改变触发
    GRF_EVENT_INSERT,                           //控件插入事件
    GRF_EVENT_REFRESH,                          //控件刷新事件
    GRF_EVENT_READY,                            //控件应用事件
    GRF_EVENT_CANCEL,                           //控件退出事件
    GRF_EVENT_DELETE,                        //控件删除事件
}grf_event_e;
//手动发送事件(返回0：控件在事件中被删除，返回1，未被删除)
s32 grf_event_send(grf_ctrl_t* ctrl_t, grf_event_e event, const void * data);
//获取用户自定义参数
//void* grf_event_get_data(void);
//获取GRF_EVENT_VALUE_CHANGED 事件的值
//void* grf_event_get_data();
/*********************************动画************************************/
typedef struct {
    u32 time;                   //动画时长
    u32 back_time;
    u32 back_time_delay;
    u32 value_start_a;
    u32 value_end_a;
    void *anim_cb_a;
    u32 value_start_b;
    u32 value_end_b;
    void *anim_cb_b;
    void *anim_reday_cb;

}grf_anim_set_t;
//动画设置{动画主体，主体动画时间，(返回动画时间，返回动画延时时间,若无需返回动画，则均设置为0），变化的范围值，动画回调函数（函数参数为void *与u32）支持双函数，不需要则填NULL}
s32 grf_animation_set(grf_ctrl_t* ctrl,u32 time,u32 back_time,u32 back_time_delay,s32 value_start_a,s32 value_end_a,void *anim_cb_a,s32 value_start_b,s32 value_end_b,void *anim_cb_b);
//删除全部动画
s32 grf_animation_del_all();
/*********************************label 文本控件************************************/
typedef enum 
{
    GRF_LABEL_DIS_BREAK,        //控件宽不变,超过区域换行,改变高度
    GRF_LABEL_DIS_DOT,          //控件宽高不变,文本超过区域,显示...
    GRF_LABEL_DIS_SROLL,        //控件宽高不变,文本超过区域,自动循环向前向后滚动文本
    GRF_LABEL_DIS_SROLL_CIRC,   //控件宽高不变,文本超过区域,自动循环环形滚动文本
    GRF_LABEL_DIS_CROP,         //控件宽高不变,超过的文本内容将会被剪切掉
}grf_label_dis_mode_e;
typedef enum 
{
    GRF_LABEL_ALIGN_LEFT = 1,    //文本左对齐
    GRF_LABEL_ALIGN_CENTER,      //文本居中对齐
    GRF_LABEL_ALIGN_RIGHT,       //文本右对齐
}grf_label_align_e;
//获取文本内容
char *grf_label_get_text(grf_ctrl_t* label);
//设置显示文本
s32 grf_label_set_txt(grf_ctrl_t* label,const char* txt);
//设置文字颜色
s32 grf_label_set_txt_color(grf_ctrl_t* label,grf_color_t color_t);
//设置文字大小
s32 grf_label_set_txt_size(grf_ctrl_t* label,u32 font_size);
//设置对齐方式
s32 grf_label_set_align(grf_ctrl_t* label,grf_label_align_e align_e);
//设置显示模式
s32 grf_label_set_dis_mode(grf_ctrl_t* label,grf_label_dis_mode_e dis_mode);
//设置长文本滚动速度
s32 grf_label_set_anim_speed(grf_ctrl_t* label,u16 speed);

/*********************************button 按钮控件************************************/
//设置按钮文字
s32 grf_btn_set_txt(grf_ctrl_t* btn,const char* txt);
//设置按钮文本颜色txt_state文本状态
s32 grf_btn_set_txt_color(grf_ctrl_t* btn,grf_color_t color_t,u32 txt_state);
//设置按钮文字大小
s32 grf_btn_set_txt_size(grf_ctrl_t* btn,u32 font_size);
//设置按钮显示模式  0-按钮模式 1-切换模式
s32 grf_btn_set_mode(grf_ctrl_t* btn,u8 mode);
//获取按钮状态
u32 grf_btn_get_state(grf_ctrl_t* btn);
//设置按钮状态
s32 grf_btn_set_state(grf_ctrl_t* btn,grf_obj_state_e state);
/*********************************image 图片控件************************************/

//修改显示图片
s32 grf_img_set_src(grf_ctrl_t * img,u8* img_src);
//获取显示图片
u8* grf_img_get_src(grf_ctrl_t * img);
//设置旋转角度(顺时针 0-360)
s32 grf_img_set_rotate_angel(grf_ctrl_t *img,u16 angel);
//设置旋转或缩放中心
s32 grf_img_set_pivot(grf_ctrl_t *img,grf_coord_t x,grf_coord_t y);
//设置图片缩放128缩小一倍，256原始大小，512放大一倍
s32 grf_img_zoom_setting(grf_ctrl_t *img,u16 size);
/*********************************image button 图片按钮控件************************************/

typedef enum {
    GRF_IMGBTN_STATE_REL,       //按钮的正常释放状态
    GRF_IMGBTN_STATE_PR,        //按钮的正常按下状态
    GRF_IMGBTN_STATE_DISABLED,          //正常禁用
    GRF_IMGBTN_STATE_CHECKED_RELEASED,    //按钮的切换(Toggle)释放状态
    GRF_IMGBTN_STATE_CHECKED_PRESSED,      //按钮的切换(Toggle)按下状态
    GRF_IMGBTN_STATE_CHECKED_DISABLED,       //切换的禁用的状态
    GRF_LV_IMGBTN_STATE_NUM,
}grf_imgbtn_state_e;
//设置图片按钮文字
s32 grf_imgbtn_set_txt(grf_ctrl_t* imgbtn,const char* txt);
//设置图片按钮文字颜色
s32 grf_imgbtn_set_txt_color(grf_ctrl_t* imgbtn,grf_color_t color_t,u32 txt_state);
//设置图片按钮文字大小
s32 grf_imgbtn_set_txt_size(grf_ctrl_t* imgbtn,u32 font_size);
//手动设置图片按钮状态(根据图片按钮事件手动设置状态)
s32 grf_imgbtn_set_mode(grf_ctrl_t* imgbtn,grf_imgbtn_state_e mode);
//设置图片按钮不同状态的显示图片
s32 grf_imgbtn_set_image(grf_ctrl_t* imgbtn,grf_imgbtn_state_e state,u8* img_src);

/*********************************line 线条控件************************************/
typedef struct
{
    grf_color_t color;      //线条颜色
    grf_coord_t width;      //线条宽度
    u8 opa;                 //透明度
    u8 rounded;             //圆角
} grf_line_disp_t;//线条
//设置线条显示样式
s32 grf_line_set_dis(grf_ctrl_t* line,grf_line_disp_t disp_t);
//设置线条点,可以多点折线显示
s32 grf_line_set_points(grf_ctrl_t* line, grf_point_t point_a[], u16 point_num);
/*********************************arc 弧形控件************************************/
//         270°
//     180° +  0°
//          90°
//设置弧形显示样式 part:0-背景,1-前景
s32 grf_arc_set_dis(grf_ctrl_t* arc,u8 part,grf_line_disp_t dis_t);
//设置滑块颜色
s32 grf_arc_set_knob(grf_ctrl_t* arc,grf_color_t color_t);
//设置值范围
s32 grf_arc_set_value_range(grf_ctrl_t* arc,s16 minvalue,s16 maxvalue);
//设置值
s32 grf_arc_set_value(grf_ctrl_t* arc,s16 value);
//得到值
s32 grf_arc_get_value(grf_ctrl_t* arc);
//设置旋转
s32 grf_arc_set_rotation(grf_ctrl_t* arc,u16 angle);
//设置起始角度和终止角度
s32 grf_arc_set_angles(grf_ctrl_t* arc,u16 start,u16 end);

/*********************************bar 进度条控件************************************/
//设置进度条的颜色
s32 grf_bar_set_bar_color(grf_ctrl_t* bar,grf_color_t color_t);
//设置进度值
s32 grf_bar_set_value(grf_ctrl_t* bar,s16 value);
//设置进度范围
s32 grf_bar_set_range(grf_ctrl_t* bar,s16 min,s16 max);
//获得进度值
s32 grf_bar_get_value(grf_ctrl_t* bar);

/*********************************slider 滑块进度条控件************************************/
//设置进度条的颜色
s32 grf_slider_set_bar_color(grf_ctrl_t* slider,grf_color_t color_t);
//设置进度值
s32 grf_slider_set_value(grf_ctrl_t* slider,s16 value);
//设置进度范围
s32 grf_slider_set_range(grf_ctrl_t* slider,s16 min,s16 max);
//获得进度值
s32 grf_slider_get_value(grf_ctrl_t* slider);

/*********************************sw 开关控件************************************/
//设置开关状态
s32 grf_sw_set_state(grf_ctrl_t* sw,grf_bool state);
//获取开关状态
grf_bool grf_sw_get_state(grf_ctrl_t* sw);

/*********************************cb 复选框控件************************************/
//设置显示的文字
s32 grf_cb_set_txt(grf_ctrl_t* cb, const char * txt);
//设置是否被选中
s32 grf_cb_set_checked(grf_ctrl_t* cb, grf_bool checked);
//判断是否被选中
grf_bool grf_cb_is_checked(grf_ctrl_t* cb);
//禁用控件
s32 grf_cb_set_disable(grf_ctrl_t* cb);
//判断是否被禁用
grf_bool grf_cb_is_inactive(grf_ctrl_t* cb);
/*********************************mbox 消息提示控件************************************/
//设置标题显示内容
s32 grf_title_set_txt(grf_ctrl_t* mbox, const char * txt);
//设置消息显示内容
s32 grf_mbox_set_txt(grf_ctrl_t* mbox, const char * txt);
//获得被点击的按钮序号
u16 grf_mbox_get_clicked_btn_num(grf_ctrl_t* mbox);
//设置延时自动关闭时间
s32 grf_mbox_start_auto_close(grf_ctrl_t* mbox,u16 delay_time);
//关闭弹窗
s32 grf_mbox_s_close(grf_ctrl_t* mbox);

/*********************************tileview 页控件************************************/
//新增tileview页面,(x,y)为新增页面id,左上为（0，0），tileview_dir为此页面可滑动方向
grf_ctrl_t *grf_tileview_add_tile(grf_ctrl_t* tileview,grf_coord_t x,grf_coord_t y,grf_droplist_dir_e tileview_dir);
//获取当前页面
grf_ctrl_t * grf_tileview_get_tile_id(grf_ctrl_t* tileview);
//根据对象手动切换页面
s32 grf_tileview_set_tile(grf_ctrl_t* tileview, grf_ctrl_t* ctrl,grf_bool anim_en);
//根据id手动切换页面
s32 grf_tileview_set_tile_id(grf_ctrl_t* tileview, grf_coord_t x,grf_coord_t y,grf_bool anim_en);
/*********************************txtbox 文本框控件************************************/
typedef enum 
{
    GRF_CURSOR_RIGHT,       //光标向右移动一步
    GRF_CURSOR_LEFT,        //光标向左移动一步
    GRF_CURSOR_DOWN,        //光标向下移动一步,文本域中有多行文本时才起作用
    GRF_CURSOR_UP,          //光标向上移动一步,文本域中有多行文本时才起作用
}grf_cursor_move_e;
//添加字符串
s32 grf_txtbox_add_txt(grf_ctrl_t* txtbox,const char * txt);
//添加单个字符
s32 grf_txtbox_add_char(grf_ctrl_t* txtbox,u32 txt);
//删除光标左侧一个字符
s32 grf_txtbox_del_char(grf_ctrl_t* txtbox);
//删除光标右侧一个字符
s32 grf_txtbox_del_char_forward(grf_ctrl_t* txtbox);
//设置文本内容
s32 grf_txtbox_set_text(grf_ctrl_t* txtbox, const char * txt);
//获取文本内容
char* grf_txtbox_get_text(grf_ctrl_t* txtbox);
//切换文本密码显示模式
s32 grf_txtbox_pwd_mode(grf_ctrl_t* txtbox,grf_bool en);
//光标移动一步
s32 grf_txtbox_cursor_move(grf_ctrl_t* txtbox,grf_cursor_move_e move_dir);
/********************************list 列表控件************************************/
//添加按钮
grf_ctrl_t* grf_list_add_btn(grf_ctrl_t* list,u8* img_src, const char *txt);
//删除某个按钮
s32 grf_list_del_btn(grf_ctrl_t* list,u16 btn_num);
//删除全部按钮
s32 grf_list_remove_all(grf_ctrl_t* list);
//得到列表的指定子对象
grf_ctrl_t* grf_list_get_index_btn(grf_ctrl_t* list,u16 btnNum);
//得到按钮的选中项id
u32 grf_list_get_select_index(grf_ctrl_t* ctrl);
//设置指定按钮的文本
s32 grf_list_set_index_str(grf_ctrl_t* list,u16 index,const char *txt);
//得到指定按钮的文本
char* grf_list_get_index_str(grf_ctrl_t* list,u16 index);
//得到指定按钮的图片对象
//grf_ctrl_t* grf_list_get_index_img(grf_ctrl_t* list,u16 index);
//得到指定按钮的标签对象
grf_ctrl_t* grf_list_get_index_label(grf_ctrl_t* list,u16 index);
//将某列表项按钮处于聚焦状态
s32 grf_list_focus(grf_ctrl_t* list,u16 index);
/********************************droplist 下拉列表控件************************************/

//增加或者改变下拉菜单的某一项
s32 grf_droplist_add_option(grf_ctrl_t* droplist, const char * option, u16 index);
//删除某一项
s32 grf_droplist_del_option(grf_ctrl_t* droplist,u16 index);
//设置所有下拉菜单项
s32 grf_droplist_set_options(grf_ctrl_t* droplist, const char * options[],u16 options_num);
//选中某个选项
s32 grf_droplist_set_selected(grf_ctrl_t* droplist,u16 sel_opt);
//获取选中项的编号
u16 grf_droplist_get_selected(grf_ctrl_t* droplist);
//获取被选中项的内容
s32 grf_droplist_get_selected_str(grf_ctrl_t* droplist,char* buf,u16 bufsize);
//将下拉框展开
s32 grf_droplist_open(grf_ctrl_t* droplist);
//将下拉框收缩
s32 grf_droplist_close(grf_ctrl_t* droplist);
/********************************rollist 滚轮列表控件************************************/
typedef enum {
    GRF_ROLLER_MODE_NORMAL,          //正常滚动模式
    GRF_ROLLER_MODE_INIFINITE,       //循环滚动模式
}grf_rollist_mode_t;
//增加或者修改某个选项
s32 grf_rollist_add_option(grf_ctrl_t* rollist, const char *options,u16 index);
//删除某个选项
s32 grf_rollist_del_option(grf_ctrl_t* rollist,u16 index);
//设置选择项
s32 grf_rollist_set_options(grf_ctrl_t* rollist, const char *options[],u16 options_num,grf_rollist_mode_t mode);
//选中某个选项
s32 grf_rollist_set_selected(grf_ctrl_t* rollist, u16 sel_opt,grf_bool anim_en);
//获取选中项的编号
s32 grf_rollist_get_selected(grf_ctrl_t* rollist);
//获取被选中项的内容
s32 grf_rollist_get_selected_str(grf_ctrl_t* rollist,char* buf,u16 bufsize);
/********************************chart 图表控件************************************/
typedef struct
{
    grf_coord_t *points;
    grf_color_t color;
} grf_chart_series_t;
typedef enum 
{
    GRF_CHART_AXIS_PRIMARY_Y     = 0x00,        //左轴
    GRF_CHART_AXIS_SECONDARY_Y   = 0x01,        //右轴
    GRF_CHART_AXIS_PRIMARY_X     = 0x02,        //底部轴
    GRF_CHART_AXIS_SECONDARY_X   = 0x04,        //顶部轴
    GRF_CHART_AXIS_LAST
}grf_chart_axis_t;

//添加线条
grf_chart_series_t *grf_chart_add_series(grf_ctrl_t * chart, grf_color_t color,grf_chart_axis_t axis);

//给线条设置点
s32 grf_chart_set_points(grf_ctrl_t* chart,grf_chart_series_t* ser, grf_coord_t y_array[]);
//添加新的数据点
s32 grf_chart_set_next(grf_ctrl_t* chart,grf_chart_series_t* ser,grf_coord_t x);
//刷新图表
s32 grf_chart_refresh(grf_ctrl_t* chart);
//删除线条
s32 grf_chart_series_remove(grf_ctrl_t* chart,grf_chart_series_t * ser);
/********************************table 表格控件************************************/
//设置单元格内容
s32 grf_table_set_cell_value(grf_ctrl_t* table, u16 row, u16 col, const char* txt);
//合并右侧单元格
s32 grf_table_set_cell_merge_right(grf_ctrl_t* table,u16 row, u16 col);
//表格样式 (表格线条颜色，宽度，透明度，表格内部填充透明度，颜色)
s32 grf_table_set_cell_wrap(grf_ctrl_t * table, grf_color_t line_color_t,u8 table_line_width,u8 table_line_opa, u8 table_opa,grf_color_t color_t);

/********************************spinbox 数据框控件************************************/
//设置数值
s32 grf_spinbox_set_value(grf_ctrl_t* spinbox, s32 value);
//获取当前的值
s32 grf_spinbox_get_value(grf_ctrl_t* spinbox);
//光标右移
s32 grf_spinbox_step_next(grf_ctrl_t* spinbox);
//光标左移
s32 grf_spinbox_step_prev(grf_ctrl_t* spinbox);
//光标位数据增加step
s32 grf_spinbox_increment(grf_ctrl_t* spinbox);
//光标位数据递减step
s32 grf_spinbox_decrement(grf_ctrl_t* spinbox);

/*************************************GIF控件****************************************/
//GIF重置（重新开始播放）
s32 grf_gif_reset_play(grf_ctrl_t *gif);
//暂停gif播放
s32 grf_gif_pause(grf_ctrl_t *gif);
//恢复gif播放
s32 grf_gif_resume(grf_ctrl_t *gif);
//设置播放次数
s32 grf_gif_play_count(grf_ctrl_t *gif,u32 count);
//设置gif图片
s32 grf_gif_set_src(grf_ctrl_t * ctrl_t,u8* gif_src);
/*************************************二维码控件****************************************/
//更新二维码数据
s32 grf_qrcode_updata_data(grf_ctrl_t* ctrl_t,char* txt);
/*************************************video控件****************************************/
typedef enum {
    GRF_VIDEO_PLAY,          //开始播放
    GRF_VIDEO_STOP,            //停止播放
    GRF_VIDEO_PAUSE,           //暂停
    GRF_VIDEO_RESUME,          //恢复播放
}grf_video_state_e;
s32 grf_video_set_pos(grf_ctrl_t* ctrl_t,u16 left_x,u16 left_y,u16 width,u16 height);
s32 grf_video_set_src(grf_ctrl_t* ctrl_t,u8* video_file);
s32 grf_video_set_state(grf_ctrl_t* ctrl_t,grf_video_state_e state);
grf_video_state_e grf_video_get_state(grf_ctrl_t* ctrl_t);
s32 grf_video_set_volum(grf_ctrl_t* ctrl_t,u8 volum);
/*************************************英文键盘控件****************************************/
//将键盘与文本框匹配（写在txtbox事件函数中，event-GRF_EVENT_FOCUSED）
s32 grf_keyboard_set_txtbox(grf_ctrl_t* keyboard,grf_ctrl_t* txtbox);




#ifdef __cplusplus
} /* extern "C" */
#endif
#endif
