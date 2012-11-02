/*
 *      menu-cache.h
 *
 *      libmenu-cache is a small convinient library used to access
 *      caches of freedesktop.org menus generated by menu-cache-gen.
 *
 *      Copyright 2008 PCMan <pcman.tw@gmail.com>
 *
 *      This program is free software; you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation; either version 2 of the License, or
 *      (at your option) any later version.
 *
 *      This program is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *
 *      You should have received a copy of the GNU General Public License
 *      along with this program; if not, write to the Free Software
 *      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *      MA 02110-1301, USA.
 */

#ifndef __MENU_CACHE_H__
#define __MENU_CACHE_H__

#include <glib.h>

G_BEGIN_DECLS

#define    MENU_CACHE_ITEM(x)    ((MenuCacheItem*)x)
#define    MENU_CACHE_DIR(x)    ((MenuCacheDir*)x)
#define    MENU_CACHE_APP(x)    ((MenuCacheApp*)x)

typedef struct _MenuCacheItem MenuCacheItem;
typedef struct _MenuCacheDir MenuCacheDir;
typedef struct _MenuCacheApp MenuCacheApp;
typedef struct _MenuCache MenuCache;

typedef enum _MenuCacheType
{
    MENU_CACHE_TYPE_NONE,
    MENU_CACHE_TYPE_DIR,
    MENU_CACHE_TYPE_APP,
    MENU_CACHE_TYPE_SEP
}MenuCacheType;

typedef enum _MenuCacheShowFlag
{
    SHOW_IN_LXDE = 1 << 0,
    SHOW_IN_GNOME = 1 << 1,
    SHOW_IN_KDE = 1 << 2,
    SHOW_IN_XFCE = 1 << 3,
    SHOW_IN_ROX = 1 << 4,
    N_KNOWN_DESKTOPS = 5
}MenuCacheShowFlag;

typedef enum _MenuCacheItemFlag
{
    FLAG_USE_TERMINAL = 1 << 0,
    FLAG_USE_SN = 1 << 1
}MenuCacheItemFlag;

void menu_cache_init(int flags);

MenuCache* menu_cache_lookup( const char* menu_name );
MenuCache* menu_cache_lookup_sync( const char* menu_name );
/* MenuCache* menu_cache_lookup_by_cache_id( const char* md5 ); */

MenuCache* menu_cache_ref(MenuCache* cache);
void menu_cache_unref(MenuCache* cache);

gboolean menu_cache_reload( MenuCache* cache );

#ifndef G_DISABLE_DEPRECATED
MenuCacheDir* menu_cache_get_root_dir( MenuCache* cache );
MenuCacheDir* menu_cache_get_dir_from_path( MenuCache* cache, const char* path );
#endif
MenuCacheDir* menu_cache_dup_root_dir( MenuCache* cache );
MenuCacheItem* menu_cache_item_from_path( MenuCache* cache, const char* path );

typedef struct _MenuCacheNotifyId* MenuCacheNotifyId;
typedef void (*MenuCacheReloadNotify)(MenuCache* cache, gpointer user_data);

MenuCacheNotifyId menu_cache_add_reload_notify(MenuCache* cache,
                                               MenuCacheReloadNotify func,
                                               gpointer user_data);
void menu_cache_remove_reload_notify(MenuCache* cache, MenuCacheNotifyId notify_id);

guint32 menu_cache_get_desktop_env_flag( MenuCache* cache, const char* desktop_env );


MenuCacheItem* menu_cache_item_ref(MenuCacheItem* item);
void menu_cache_item_unref(MenuCacheItem* item);

MenuCacheType menu_cache_item_get_type( MenuCacheItem* item );
const char* menu_cache_item_get_id( MenuCacheItem* item );
const char* menu_cache_item_get_name( MenuCacheItem* item );
const char* menu_cache_item_get_comment( MenuCacheItem* item );
const char* menu_cache_item_get_icon( MenuCacheItem* item );

const char* menu_cache_item_get_file_basename( MenuCacheItem* item );
const char* menu_cache_item_get_file_dirname( MenuCacheItem* item );
char* menu_cache_item_get_file_path( MenuCacheItem* item );

#ifndef G_DISABLE_DEPRECATED
MenuCacheDir* menu_cache_item_get_parent( MenuCacheItem* item );
#endif
MenuCacheDir* menu_cache_item_dup_parent( MenuCacheItem* item );

GSList* menu_cache_dir_get_children( MenuCacheDir* dir );
char* menu_cache_dir_make_path( MenuCacheDir* dir );


const char* menu_cache_app_get_exec( MenuCacheApp* app );
const char* menu_cache_app_get_working_dir( MenuCacheApp* app );

guint32 menu_cache_app_get_show_flags( MenuCacheApp* app );
gboolean menu_cache_app_get_is_visible( MenuCacheApp* app, guint32 de_flags );

gboolean menu_cache_app_get_use_terminal( MenuCacheApp* app );
gboolean menu_cache_app_get_use_sn( MenuCacheApp* app );

GSList* menu_cache_list_all_apps(MenuCache* cache);

/*
MenuCacheApp* menu_cache_find_app_by_exec( const char* exec );
*/
G_END_DECLS

#endif

