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

#ifndef _MenuUpDownPushButtonSet_H
#define _MenuUpDownPushButtonSet_H

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

#include "_ComponentsBaseComponent.h"
#include "_CoreKeyPressHandler.h"
#include "_MenuPushButton.h"

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

/* Forward declaration of the class Menu::UpDownPushButtonSet */
#ifndef _MenuUpDownPushButtonSet_
  EW_DECLARE_CLASS( MenuUpDownPushButtonSet )
#define _MenuUpDownPushButtonSet_
#endif


/* Deklaration of class : 'Menu::UpDownPushButtonSet' */
EW_DEFINE_FIELDS( MenuUpDownPushButtonSet, ComponentsBaseComponent )
  EW_PROPERTY( OnUpButtonActivated, XSlot )
  EW_PROPERTY( OnDownButtonActivated, XSlot )
  EW_OBJECT  ( UpButton,        MenuPushButton )
  EW_OBJECT  ( DownButton,      MenuPushButton )
  EW_PROPERTY( UpButtonTitle,   XString )
  EW_PROPERTY( DownButtonTitle, XString )
  EW_PROPERTY( DownButtonEnabled, XBool )
EW_END_OF_FIELDS( MenuUpDownPushButtonSet )

/* Virtual Method Table (VMT) for the class : 'Menu::UpDownPushButtonSet' */
EW_DEFINE_METHODS( MenuUpDownPushButtonSet, ComponentsBaseComponent )
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
  EW_METHOD( OnShortDownKeyActivated, void )( MenuUpDownPushButtonSet _this )
  EW_METHOD( OnShortUpKeyActivated, void )( MenuUpDownPushButtonSet _this )
  EW_METHOD( OnShortEnterKeyActivated, void )( ComponentsBaseComponent _this )
  EW_METHOD( OnShortHomeKeyActivated, void )( ComponentsBaseComponent _this )
  EW_METHOD( OnLongDownKeyActivated, void )( ComponentsBaseComponent _this )
  EW_METHOD( OnLongUpKeyActivated, void )( ComponentsBaseComponent _this )
  EW_METHOD( OnLongEnterKeyActivated, void )( ComponentsBaseComponent _this )
  EW_METHOD( OnLongHomeKeyActivated, void )( ComponentsBaseComponent _this )
  EW_METHOD( OnShortMagicKeyActivated, void )( ComponentsBaseComponent _this )
  EW_METHOD( OnSetDDModeEnabled, void )( MenuUpDownPushButtonSet _this, XBool value )
  EW_METHOD( OnDownKeyReleased, void )( ComponentsBaseComponent _this )
  EW_METHOD( OnUpKeyReleased,   void )( ComponentsBaseComponent _this )
EW_END_OF_METHODS( MenuUpDownPushButtonSet )

/* 'C' function for method : 'Menu::UpDownPushButtonSet.OnShortDownKeyActivated()' */
void MenuUpDownPushButtonSet_OnShortDownKeyActivated( MenuUpDownPushButtonSet _this );

/* 'C' function for method : 'Menu::UpDownPushButtonSet.OnShortUpKeyActivated()' */
void MenuUpDownPushButtonSet_OnShortUpKeyActivated( MenuUpDownPushButtonSet _this );

/* 'C' function for method : 'Menu::UpDownPushButtonSet.OnSetDDModeEnabled()' */
void MenuUpDownPushButtonSet_OnSetDDModeEnabled( MenuUpDownPushButtonSet _this, 
  XBool value );

/* 'C' function for method : 'Menu::UpDownPushButtonSet.OnActivateSlot()' */
void MenuUpDownPushButtonSet_OnActivateSlot( MenuUpDownPushButtonSet _this, XObject 
  sender );

/* 'C' function for method : 'Menu::UpDownPushButtonSet.OnSetUpButtonTitle()' */
void MenuUpDownPushButtonSet_OnSetUpButtonTitle( MenuUpDownPushButtonSet _this, 
  XString value );

/* 'C' function for method : 'Menu::UpDownPushButtonSet.OnSetDownButtonTitle()' */
void MenuUpDownPushButtonSet_OnSetDownButtonTitle( MenuUpDownPushButtonSet _this, 
  XString value );

/* 'C' function for method : 'Menu::UpDownPushButtonSet.OnSetDownButtonEnabled()' */
void MenuUpDownPushButtonSet_OnSetDownButtonEnabled( MenuUpDownPushButtonSet _this, 
  XBool value );

#ifdef __cplusplus
  }
#endif

#endif /* _MenuUpDownPushButtonSet_H */

/* Embedded Wizard */
