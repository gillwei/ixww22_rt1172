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

#ifndef _HomeHOM13_SpeedVisualizer_H
#define _HomeHOM13_SpeedVisualizer_H

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

#include "_ComponentsDDModeMask.h"
#include "_CoreKeyPressHandler.h"
#include "_CoreSystemEventHandler.h"
#include "_CoreTimer.h"
#include "_HomeBaseHome.h"
#include "_HomeSpeedCircle.h"
#include "_PopPOP16_NaviLoadingUI.h"
#include "_ViewsImage.h"
#include "_ViewsRectangle.h"
#include "_ViewsText.h"
#include "_ViewsWallpaper.h"

/* Forward declaration of the class Components::BaseMainBG */
#ifndef _ComponentsBaseMainBG_
  EW_DECLARE_CLASS( ComponentsBaseMainBG )
#define _ComponentsBaseMainBG_
#endif

/* Forward declaration of the class Core::DialogContext */
#ifndef _CoreDialogContext_
  EW_DECLARE_CLASS( CoreDialogContext )
#define _CoreDialogContext_
#endif

/* Forward declaration of the class Core::Group */
#ifndef _CoreGroup_
  EW_DECLARE_CLASS( CoreGroup )
#define _CoreGroup_
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

/* Forward declaration of the class Home::HOM13_SpeedVisualizer */
#ifndef _HomeHOM13_SpeedVisualizer_
  EW_DECLARE_CLASS( HomeHOM13_SpeedVisualizer )
#define _HomeHOM13_SpeedVisualizer_
#endif


/* Deklaration of class : 'Home::HOM13_SpeedVisualizer' */
EW_DEFINE_FIELDS( HomeHOM13_SpeedVisualizer, HomeBaseHome )
  EW_OBJECT  ( SpeedCircle,     HomeSpeedCircle )
  EW_OBJECT  ( SpeedVisualizerTitle, ViewsImage )
  EW_OBJECT  ( SpeedLimitUnit,  ViewsImage )
  EW_OBJECT  ( SpeedLimitText,  ViewsText )
  EW_OBJECT  ( SpeedLimitTitle, ViewsImage )
  EW_OBJECT  ( StatusShadow,    ViewsWallpaper )
  EW_OBJECT  ( VehicleDataReceivedEventHandler, CoreSystemEventHandler )
  EW_OBJECT  ( SpeedLimitUpdateEventHandler, CoreSystemEventHandler )
  EW_OBJECT  ( Timer,           CoreTimer )
  EW_OBJECT  ( SpeedUpdateTimer, CoreTimer )
  EW_PROPERTY( SpeedLimit,      XInt32 )
  EW_PROPERTY( SpeedUnit,       XEnum )
  EW_VARIABLE( Ascending,       XBool )
EW_END_OF_FIELDS( HomeHOM13_SpeedVisualizer )

/* Virtual Method Table (VMT) for the class : 'Home::HOM13_SpeedVisualizer' */
EW_DEFINE_METHODS( HomeHOM13_SpeedVisualizer, HomeBaseHome )
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
  EW_METHOD( OnShortDownKeyActivated, void )( ComponentsBaseComponent _this )
  EW_METHOD( OnShortUpKeyActivated, void )( ComponentsBaseComponent _this )
  EW_METHOD( OnShortEnterKeyActivated, void )( HomeBaseHome _this )
  EW_METHOD( OnShortHomeKeyActivated, void )( HomeBaseHome _this )
  EW_METHOD( OnLongDownKeyActivated, void )( ComponentsBaseComponent _this )
  EW_METHOD( OnLongUpKeyActivated, void )( ComponentsBaseComponent _this )
  EW_METHOD( OnLongEnterKeyActivated, void )( HomeHOM13_SpeedVisualizer _this )
  EW_METHOD( OnLongHomeKeyActivated, void )( ComponentsBaseComponent _this )
  EW_METHOD( OnShortMagicKeyActivated, void )( ComponentsBaseComponent _this )
  EW_METHOD( OnSetDDModeEnabled, void )( ComponentsBaseMainBG _this, XBool value )
  EW_METHOD( OnDownKeyReleased, void )( ComponentsBaseComponent _this )
  EW_METHOD( OnUpKeyReleased,   void )( ComponentsBaseComponent _this )
  EW_METHOD( ReturnToHome,      void )( HomeBaseHome _this )
EW_END_OF_METHODS( HomeHOM13_SpeedVisualizer )

/* The method Init() is invoked automatically after the component has been created. 
   This method can be overridden and filled with logic containing additional initialization 
   statements. */
void HomeHOM13_SpeedVisualizer_Init( HomeHOM13_SpeedVisualizer _this, XHandle aArg );

/* 'C' function for method : 'Home::HOM13_SpeedVisualizer.OnLongEnterKeyActivated()' */
void HomeHOM13_SpeedVisualizer_OnLongEnterKeyActivated( HomeHOM13_SpeedVisualizer _this );

/* This slot method is executed when the associated system event handler 'SystemEventHandler' 
   receives an event. */
void HomeHOM13_SpeedVisualizer_OnVehicleDataReceivedSlot( HomeHOM13_SpeedVisualizer _this, 
  XObject sender );

/* This slot method is executed when the associated system event handler 'SystemEventHandler' 
   receives an event. */
void HomeHOM13_SpeedVisualizer_OnSpeedLimitUpdateSlot( HomeHOM13_SpeedVisualizer _this, 
  XObject sender );

/* 'C' function for method : 'Home::HOM13_SpeedVisualizer.OnSetSpeedUnit()' */
void HomeHOM13_SpeedVisualizer_OnSetSpeedUnit( HomeHOM13_SpeedVisualizer _this, 
  XEnum value );

/* 'C' function for method : 'Home::HOM13_SpeedVisualizer.OnSetSpeedLimit()' */
void HomeHOM13_SpeedVisualizer_OnSetSpeedLimit( HomeHOM13_SpeedVisualizer _this, 
  XInt32 value );

/* 'C' function for method : 'Home::HOM13_SpeedVisualizer.OnTimerSlot()' */
void HomeHOM13_SpeedVisualizer_OnTimerSlot( HomeHOM13_SpeedVisualizer _this, XObject 
  sender );

/* 'C' function for method : 'Home::HOM13_SpeedVisualizer.OnSpeedUpdateSlot()' */
void HomeHOM13_SpeedVisualizer_OnSpeedUpdateSlot( HomeHOM13_SpeedVisualizer _this, 
  XObject sender );

#ifdef __cplusplus
  }
#endif

#endif /* _HomeHOM13_SpeedVisualizer_H */

/* Embedded Wizard */
