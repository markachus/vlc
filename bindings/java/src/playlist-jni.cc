/*****************************************************************************
 * playlist-jni.cc: JNI native playlist functions for VLC Java Bindings
 *****************************************************************************
 * Copyright (C) 1998-2006 the VideoLAN team
 *
 * Authors: Filippo Carone <filippo@carone.org>
 *
 *
 * $Id $
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111, USA.
 *****************************************************************************/

/* These are a must*/
#include <jni.h>
#include <vlc/libvlc.h>
#include <unistd.h>
#include <stdio.h>

/* JVLC internal imports, generated by gcjh */
#include "../includes/Playlist.h"

#include "utils.h"


JNIEXPORT jint JNICALL Java_org_videolan_jvlc_Playlist__1playlist_1add (JNIEnv *env, jobject _this, jstring uri, jstring name,  jobjectArray options) {

    INIT_FUNCTION ;
    
    int res = 0;
    int i_options = 0;
    const char** ppsz_options = NULL;
    const char* psz_uri  = env->GetStringUTFChars( uri, 0 );
    const char* psz_name = env->GetStringUTFChars( name, 0 );

    if ( options != NULL ) {
        i_options = ( int ) env->GetArrayLength( ( jarray ) options ) + 1;
        ppsz_options = ( const char ** ) malloc( i_options * sizeof( char* ) );
        sprintf( ( char * ) ppsz_options[0], "%s", "jvlc" );

        for (int i = 0; i < i_options - 1; i++) {
            ppsz_options[ i+1 ] =
                env->GetStringUTFChars( ( jstring ) env->GetObjectArrayElement( options, i ), 0 );
        }
        res = libvlc_playlist_add_extended( ( libvlc_instance_t * ) instance, psz_uri, psz_name, i_options, ppsz_options, exception );

        CHECK_EXCEPTION_FREE;
        
    } else {
        res = libvlc_playlist_add( ( libvlc_instance_t * ) instance, psz_uri, psz_name, exception );
        
        CHECK_EXCEPTION_FREE;
    }
    
    if (psz_uri != NULL) {
        env->ReleaseStringUTFChars( uri, psz_uri );
    }

    if (psz_name != NULL) {
        env->ReleaseStringUTFChars( name, psz_name );
    }

    return res;
}


JNIEXPORT void JNICALL Java_org_videolan_jvlc_Playlist__1play (JNIEnv *env, jobject _this, jint id, jobjectArray options)
{

    INIT_FUNCTION;
    
    int i_options = 0;
    const char** ppsz_options = NULL;

    if ( options != NULL ) {
       i_options = ( int ) env->GetArrayLength( ( jarray ) options );
       ppsz_options = ( const char ** ) malloc( i_options * sizeof( char* ) );
       for ( int i = 0; i < i_options - 1; i++ ) {
           ppsz_options[ i ] = 
               env->GetStringUTFChars( ( jstring ) env->GetObjectArrayElement( options, i ), 0 );
       }
    }

    libvlc_playlist_play( ( libvlc_instance_t * ) instance, id, i_options, ( char **  ) ppsz_options, exception );

    CHECK_EXCEPTION_FREE;
}


JNIEXPORT void JNICALL Java_org_videolan_jvlc_Playlist__1pause (JNIEnv *env, jobject _this)
{
    INIT_FUNCTION ;

    libvlc_playlist_pause( ( libvlc_instance_t* ) instance, exception );

    CHECK_EXCEPTION_FREE ;
}

JNIEXPORT void JNICALL Java_org_videolan_jvlc_Playlist__1stop (JNIEnv *env, jobject _this)
{
    INIT_FUNCTION ;

    libvlc_playlist_stop( ( libvlc_instance_t* ) instance, exception );
    
    while ( libvlc_playlist_isplaying( (libvlc_instance_t*) instance, exception ) )
    {
        usleep(100);
    }
    

    CHECK_EXCEPTION_FREE ;
}

JNIEXPORT void JNICALL Java_org_videolan_jvlc_Playlist__1next (JNIEnv *env, jobject _this)
{
    INIT_FUNCTION ;
    
    libvlc_playlist_next( ( libvlc_instance_t* ) instance, exception );

    CHECK_EXCEPTION_FREE ;
}

JNIEXPORT void JNICALL Java_org_videolan_jvlc_Playlist__1prev (JNIEnv *env, jobject _this)
{
    INIT_FUNCTION ;
    
    libvlc_playlist_prev( (libvlc_instance_t*) instance, exception );

    CHECK_EXCEPTION_FREE ;
}

JNIEXPORT void JNICALL Java_org_videolan_jvlc_Playlist__1clear (JNIEnv *env, jobject _this)
{
    INIT_FUNCTION ;

    libvlc_playlist_clear( (libvlc_instance_t*) instance, exception );

    CHECK_EXCEPTION_FREE ;
}

JNIEXPORT void JNICALL Java_org_videolan_jvlc_Playlist__1deleteItem (JNIEnv *env, jobject _this, jint itemID)
{
    INIT_FUNCTION ;

    libvlc_playlist_delete_item( ( libvlc_instance_t * ) instance, itemID, exception );

    CHECK_EXCEPTION_FREE ;
}


JNIEXPORT jint JNICALL Java_org_videolan_jvlc_Playlist__1itemsCount (JNIEnv *env, jobject _this)
{
    INIT_FUNCTION ;
    int res = 0;

    res = libvlc_playlist_items_count( (libvlc_instance_t*) instance, exception );

    CHECK_EXCEPTION_FREE ;

    return res;

}

JNIEXPORT jint JNICALL Java_org_videolan_jvlc_Playlist__1isRunning (JNIEnv *env, jobject _this)
{
    INIT_FUNCTION ;
    int res = 0;

    res = libvlc_playlist_isplaying( (libvlc_instance_t*) instance, exception );

    CHECK_EXCEPTION_FREE ;

    return res;
}

JNIEXPORT void JNICALL Java_org_videolan_jvlc_Playlist__1setLoop
  (JNIEnv *env, jobject _this, jboolean loop)
{
   INIT_FUNCTION ;

   libvlc_playlist_loop( (libvlc_instance_t*) instance, loop, exception );

   CHECK_EXCEPTION_FREE ;
   
}   
