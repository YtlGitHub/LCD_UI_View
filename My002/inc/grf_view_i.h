#ifndef __GRF_VIEW_I_H_
#define __GRF_VIEW_I_H_


#ifdef __cplusplus
extern "C" {
#endif

#include "grf_typedef.h"

typedef void grf_view_t;
typedef enum 
{
    GRF_LAYER_UI,           //UI图层
    GRF_LAYER_STATE,        //状态图层
    GRF_LAYER_TOP,          //顶层图层
}grf_layer_se;
    
//设置显示图层位置  
s32 grf_view_set_layer(u32 v_id,grf_layer_se layer);        
//设置显示视图             
s32 grf_view_set_dis_view(u32 v_id);                                    
//获取当前视图ID
s32 grf_view_get_cur_id(grf_layer_se layer);     
//获取对应ID的视图                         
grf_view_t* grf_view_get_from_id(u32 v_id);                           
//隐藏图层
s32 grf_view_hide_layer(grf_layer_se layer);
//加载视图资源,但是不显示
s32 grf_view_load(u32 v_num);
//设置视图背景图片
s32 grf_view_set_bg(u32 v_id,u8* img_name);
//设置视图背景色
s32 grf_view_set_bgcolor(u32 v_id,grf_color_t color_t);
//得到视图宽高
s32 grf_view_get_dis_wh(grf_size_t* disp_size);
































#ifdef __cplusplus
} /* extern "C" */
#endif




#endif
