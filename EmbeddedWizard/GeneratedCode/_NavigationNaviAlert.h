/*******************************************************************************
*
* E M B E D D E D   W I Z A R D   P R O J E C T
*
*                                                Copyright (c) TARA Systems GmbH
*                                    written by Paul Banach and Manfred Schweyer
*
********************************************************************************
*
* This file was generated automatically by Embedded Wizard Studio.
*
* Please do not make any modifications of this file! The modifications are lost
* when the file is generated again by Embedded Wizard Studio!
*
* The template of this heading text can be found in the file 'head.ewt' in the
* directory 'Platforms' of your Embedded Wizard installation directory. If you
* wish to adapt this text, please copy the template file 'head.ewt' into your
* project directory and edit the copy only. Please avoid any modifications of
* the original template file!
*
* Version  : 11.00
* Profile  : iMX_RT
* Platform : NXP.iMX_RT_VGLite.RGBA8888
*
*******************************************************************************/

#ifndef _NavigationNaviAlert_H
#define _NavigationNaviAlert_H

#ifdef __cplusplus
  extern "C"
  {
#endif

#include "ewrte.h"
#if EW_RTE_VERSION != 0x000B0000
  #error Wrong version of Embedded Wizard Runtime Environment.
#endif

#include "ewgfx.h"
#if EW_GFX_VERSION != 0x000B0000
  #error Wrong version of Embedded Wizard Graphics Engine.
#endif

#include "_CoreGroup.h"
#include "_CoreSystemEventHandler.h"
#include "_CoreTimer.h"
#include "_EffectsRectEffect.h"
#include "_NavigationNaviAlertMessage.h"
#include "_ViewsRectangle.h"
#include "_ViewsText.h"

/* Forward declaration of the class Core::DialogContext */
#ifndef _CoreDialogContext_
  EW_DECLARE_CLASS( CoreDialogContext )
#define _CoreDialogContext_
#endif

/* Forward declaration of the class Core::KeyPressHandler */
#ifndef _CoreKeyPressHandler_
  EW_DECLARE_CLASS( CoreKeyPressHandler )
#define _CoreKeyPressHandler_
#endif

/* Forward declaration of the class Core::LayoutContext */
#ifndef _CoreLayoutContext_
  EW_DECLARE_CLASS( CoreLayoutContext )
#define _CoreLayoutContext_
#endif

/* Forward declaration of the class Core::TaskQueue */
#ifndef _CoreTaskQueue_
  EW_DECLARE_CLASS( CoreTaskQueue )
#define _CoreTaskQueue_
#endif

/* Forward declaration of the class Core::View */
#ifndef _CoreView_
  EW_DECLARE_CLASS( CoreView )
#define _CoreView_
#endif

/* Forward declaration of the class Effects::Fader */
#ifndef _EffectsFader_
  EW_DECLARE_CLASS( EffectsFader )
#define _EffectsFader_
#endif

/* Forward declaration of the class Graphics::Canvas */
#ifndef _GraphicsCanvas_
  EW_DECLARE_CLASS( GraphicsCanvas )
#define _GraphicsCanvas_
#endif

/* Forward declaration of the class Navigation::NaviAlert */
#ifndef _NavigationNaviAlert_
  EW_DECLARE_CLASS( NavigationNaviAlert )
#define _NavigationNaviAlert_
#endif


/* Deklaration of class : 'Navigation::NaviAlert' */
EW_DEFINE_FIELDS( NavigationNaviAlert, CoreGroup )
  EW_PROPERTY( DismissAlertSignal, XSlot )
  EW_OBJECT  ( AlertMessage,    NavigationNaviAlertMessage )
  EW_OBJECT  ( NaviDistBg,      ViewsRectangle )
  EW_OBJECT  ( DistUnit,        ViewsText )
  EW_OBJECT  ( Distance,        ViewsText )
  EW_OBJECT  ( SuspendTimer,    CoreTimer )
  EW_OBJECT  ( NaviEventShrinkEffect, EffectsRectEffect )
  EW_OBJECT  ( AlertDistanceUpdate, CoreSystemEventHandler )
  EW_ARRAY   ( DistUnitTextArray, XString, [2])
  EW_ARRAY   ( SpeedUnitTextArray, XString, [2])
  EW_VARIABLE( IsEnlargeFinished, XBool )
  EW_VARIABLE( IsShrinkFinished, XBool )
EW_END_OF_FIELDS( NavigationNaviAlert )

/* Virtual Method Table (VMT) for the class : 'Navigation::NaviAlert' */
EW_DEFINE_METHODS( NavigationNaviAlert, CoreGroup )
  EW_METHOD( initLayoutContext, void )( CoreRectView _this, XRect aBounds, CoreOutline 
    aOutline )
  EW_METHOD( GetRoot,           CoreRoot )( CoreView _this )
  EW_METHOD( Draw,              void )( CoreGroup _this, GraphicsCanvas aCanvas, 
    XRect aClip, XPoint aOffset, XInt32 aOpacity, XBool aBlend )
  EW_METHOD( HandleEvent,       XObject )( CoreView _this, CoreEvent aEvent )
  EW_METHOD( CursorHitTest,     CoreCursorHit )( CoreGroup _this, XRect aArea, XInt32 
    aFinger, XInt32 aStrikeCount, CoreView aDedicatedView, XSet aRetargetReason )
  EW_METHOD( ArrangeView,       XPoint )( CoreRectView _this, XRect aBounds, XEnum 
    aFormation )
  EW_METHOD( MoveView,          void )( CoreRectView _this, XPoint aOffset, XBool 
    aFastMove )
  EW_METHOD( GetExtent,         XRect )( CoreRectView _this )
  EW_METHOD( ChangeViewState,   void )( CoreGroup _this, XSet aSetState, XSet aClearState )
  EW_METHOD( OnSetBounds,       void )( CoreGroup _this, XRect value )
  EW_METHOD( OnSetFocus,        void )( CoreGroup _this, CoreView value )
  EW_METHOD( OnSetBuffered,     void )( CoreGroup _this, XBool value )
  EW_METHOD( OnGetEnabled,      XBool )( CoreGroup _this )
  EW_METHOD( OnSetEnabled,      void )( CoreGroup _this, XBool value )
  EW_METHOD( OnSetOpacity,      void )( CoreGroup _this, XInt32 value )
  EW_METHOD( OnSetVisible,      void )( CoreGroup _this, XBool value )
  EW_METHOD( IsCurrentDialog,   XBool )( CoreGroup _this )
  EW_METHOD( IsActiveDialog,    XBool )( CoreGroup _this, XBool aRecursive )
  EW_METHOD( DispatchEvent,     XObject )( CoreGroup _this, CoreEvent aEvent )
  EW_METHOD( BroadcastEvent,    XObject )( CoreGroup _this, CoreEvent aEvent, XSet 
    aFilter )
  EW_METHOD( UpdateLayout,      void )( CoreGroup _this, XPoint aSize )
  EW_METHOD( UpdateViewState,   void )( CoreGroup _this, XSet aState )
  EW_METHOD( InvalidateArea,    void )( CoreGroup _this, XRect aArea )
  EW_METHOD( GetViewAtIndex,    CoreView )( CoreGroup _this, XInt32 aIndex )
  EW_METHOD( CountViews,        XInt32 )( CoreGroup _this )
  EW_METHOD( FindNextView,      CoreView )( CoreGroup _this, CoreView aView, XSet 
    aFilter )
  EW_METHOD( FindSiblingView,   CoreView )( CoreGroup _this, CoreView aView, XSet 
    aFilter )
  EW_METHOD( RestackTop,        void )( CoreGroup _this, CoreView aView )
  EW_METHOD( Restack,           void )( CoreGroup _this, CoreView aView, XInt32 
    aOrder )
  EW_METHOD( Remove,            void )( CoreGroup _this, CoreView aView )
  EW_METHOD( Add,               void )( CoreGroup _this, CoreView aView, XInt32 
    aOrder )
EW_END_OF_METHODS( NavigationNaviAlert )

/* 'C' function for method : 'Navigation::NaviAlert.ShrinkAlert()' */
void NavigationNaviAlert_ShrinkAlert( NavigationNaviAlert _this );

/* 'C' function for method : 'Navigation::NaviAlert.OnSuspendUpdateSlot()' */
void NavigationNaviAlert_OnSuspendUpdateSlot( NavigationNaviAlert _this, XObject 
  sender );

/* 'C' function for method : 'Navigation::NaviAlert.SetAlert()' */
void NavigationNaviAlert_SetAlert( NavigationNaviAlert _this, XEnum aNaviEventType, 
  XEnum aNaviCameraType, XString aNaviEventSpeed, XString aNaviEventDist );

/* 'C' function for method : 'Navigation::NaviAlert.OnNaviEventShrinkFinishSlot()' */
void NavigationNaviAlert_OnNaviEventShrinkFinishSlot( NavigationNaviAlert _this, 
  XObject sender );

/* 'C' function for method : 'Navigation::NaviAlert.SetCamera()' */
void NavigationNaviAlert_SetCamera( NavigationNaviAlert _this, XEnum aNaviCameraType );

/* This slot method is executed when the associated system event handler 'SystemEventHandler' 
   receives an event. */
void NavigationNaviAlert_OnAlertDistanceUpdateSlot( NavigationNaviAlert _this, XObject 
  sender );

#ifdef __cplusplus
  }
#endif

#endif /* _NavigationNaviAlert_H */

/* Embedded Wizard */
