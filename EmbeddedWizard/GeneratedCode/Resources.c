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

#include "ewlocale.h"
#include "_ResourcesBitmap.h"
#include "_ResourcesExternBitmap.h"
#include "_ResourcesFont.h"
#include "Resources.h"

/* Compressed strings for the language 'Default'. */
EW_CONST_STRING_PRAGMA static const unsigned int _StringsDefault0[] =
{
  0x00000056, /* ratio 97.67 % */
  0xB8005300, 0x000A8452, 0x00CA0034, 0x0E000100, 0xDE003900, 0x10F84C34, 0x79001D00,
  0x01380216, 0x30C548C0, 0x9C50DA00, 0x000D2002, 0x3239143D, 0xA3473934, 0x00450014,
  0x44400104, 0x4E0013E3, 0x90013000, 0x000B8005, 0x08028340, 0x00000008, 0x00000000
};

/* Constant values used in this 'C' module only. */
static const XPoint _Const0000 = { 0, 0 };
static const XStringRes _Const0001 = { _StringsDefault0, 0x0002 };

/* Initializer for the class 'Resources::Bitmap' */
void ResourcesBitmap__Init( ResourcesBitmap _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  CoreResource__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ResourcesBitmap );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ResourcesBitmap );

  /* ... and initialize objects, variables, properties, etc. */
  _this->NoOfFrames = 1;

  /* Call the user defined constructor */
  ResourcesBitmap_Init( _this, aArg );
}

/* Re-Initializer for the class 'Resources::Bitmap' */
void ResourcesBitmap__ReInit( ResourcesBitmap _this )
{
  /* At first re-initialize the super class ... */
  CoreResource__ReInit( &_this->_.Super );
}

/* Finalizer method for the class 'Resources::Bitmap' */
void ResourcesBitmap__Done( ResourcesBitmap _this )
{
  /* Call the user defined destructor of the class */
  ResourcesBitmap_Done( _this );

  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( CoreResource );

  /* Don't forget to deinitialize the super class ... */
  CoreResource__Done( &_this->_.Super );
}

/* 'C' function for method : 'Resources::Bitmap.Done()' */
void ResourcesBitmap_Done( ResourcesBitmap _this )
{
  XHandle handle;

  if ( _this->bitmap == 0 )
    return;

  handle = _this->bitmap;
  EwFreeBitmap((XBitmap*)handle );
  _this->bitmap = 0;
  _this->FrameSize = _Const0000;
  _this->FrameDelay = 0;
  _this->NoOfFrames = 1;
  _this->Animated = 0;
}

/* 'C' function for method : 'Resources::Bitmap.Init()' */
void ResourcesBitmap_Init( ResourcesBitmap _this, XHandle aArg )
{
  XHandle handle;
  XInt32 noOfFrames;
  XPoint frameSize;
  XInt32 frameDelay;

  if ( aArg == 0 )
    return;

  handle = 0;
  noOfFrames = 1;
  frameSize = _Const0000;
  frameDelay = 0;
  {
    /* aArg is a pointer to the memory where the bitmap resource is stored. */
    XBitmap* bmp = EwLoadBitmap((const XBmpRes*)aArg );

    /* After the bitmap has been loaded get the size of the bitmap and store it
       in the following variables. */
    if ( bmp )
    {
      noOfFrames = bmp->NoOfVirtFrames;
      frameSize  = bmp->FrameSize;
      frameDelay = bmp->FrameDelay;
    }

    handle = (XHandle)(void*)bmp;
  }
  _this->bitmap = handle;
  _this->NoOfFrames = noOfFrames;
  _this->FrameSize = frameSize;
  _this->FrameDelay = frameDelay;
  _this->Animated = (XBool)((( _this->bitmap != 0 ) && ( _this->FrameDelay > 0 )) 
  && ( _this->NoOfFrames > 1 ));
}

/* 'C' function for method : 'Resources::Bitmap.OnSetFrameSize()' */
void ResourcesBitmap_OnSetFrameSize( ResourcesBitmap _this, XPoint value )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );
  EW_UNUSED_ARG( value );

  {
    EwThrow( EwLoadString( &_Const0001 ));
    return;
  }
}

/* Wrapper function for the virtual method : 'Resources::Bitmap.OnSetFrameSize()' */
void ResourcesBitmap__OnSetFrameSize( void* _this, XPoint value )
{
  ((ResourcesBitmap)_this)->_.VMT->OnSetFrameSize((ResourcesBitmap)_this, value );
}

/* 'C' function for method : 'Resources::Bitmap.Update()' */
void ResourcesBitmap_Update( ResourcesBitmap _this )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );
}

/* Wrapper function for the virtual method : 'Resources::Bitmap.Update()' */
void ResourcesBitmap__Update( void* _this )
{
  ((ResourcesBitmap)_this)->_.VMT->Update((ResourcesBitmap)_this );
}

/* Variants derived from the class : 'Resources::Bitmap' */
EW_DEFINE_CLASS_VARIANTS( ResourcesBitmap )
EW_END_OF_CLASS_VARIANTS( ResourcesBitmap )

/* Virtual Method Table (VMT) for the class : 'Resources::Bitmap' */
EW_DEFINE_CLASS( ResourcesBitmap, CoreResource, _.VMT, _.VMT, _.VMT, _.VMT, _.VMT, 
                 _.VMT, "Resources::Bitmap" )
  ResourcesBitmap_OnSetFrameSize,
  ResourcesBitmap_Update,
EW_END_OF_CLASS( ResourcesBitmap )

/* Include a file containing the bitmap resource : 'Resources::DefaultBitmap' */
#include "_ResourcesDefaultBitmap.h"

/* Table with links to derived variants of the bitmap resource : 'Resources::DefaultBitmap' */
EW_RES_WITHOUT_VARIANTS( ResourcesDefaultBitmap )

/* Initializer for the class 'Resources::ExternBitmap' */
void ResourcesExternBitmap__Init( ResourcesExternBitmap _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  ResourcesBitmap__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ResourcesExternBitmap );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ResourcesExternBitmap );

  /* Call the user defined constructor */
  ResourcesExternBitmap_Init( _this, aArg );
}

/* Re-Initializer for the class 'Resources::ExternBitmap' */
void ResourcesExternBitmap__ReInit( ResourcesExternBitmap _this )
{
  /* At first re-initialize the super class ... */
  ResourcesBitmap__ReInit( &_this->_.Super );
}

/* Finalizer method for the class 'Resources::ExternBitmap' */
void ResourcesExternBitmap__Done( ResourcesExternBitmap _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( ResourcesBitmap );

  /* Don't forget to deinitialize the super class ... */
  ResourcesBitmap__Done( &_this->_.Super );
}

/* 'C' function for method : 'Resources::ExternBitmap.Init()' */
void ResourcesExternBitmap_Init( ResourcesExternBitmap _this, XHandle aArg )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( aArg );

  _this->Super1.Mutable = 1;
}

/* 'C' function for method : 'Resources::ExternBitmap.OnSetName()' */
void ResourcesExternBitmap_OnSetName( ResourcesExternBitmap _this, XString value )
{
  if ( !EwCompString( _this->Name, value ))
    return;

  _this->Name = EwShareString( value );
  EwPostSignal( EwNewSlot( _this, ResourcesExternBitmap_load ), ((XObject)_this ));
}

/* The method Reload() triggers the extern bitmap object to reload the image file 
   identified by the property @Name. This method is useful if the image file content 
   has changed at the runtime. */
void ResourcesExternBitmap_Reload( ResourcesExternBitmap _this )
{
  EwPostSignal( EwNewSlot( _this, ResourcesExternBitmap_load ), ((XObject)_this ));
}

/* 'C' function for method : 'Resources::ExternBitmap.load()' */
void ResourcesExternBitmap_load( ResourcesExternBitmap _this, XObject sender )
{
  XString name;
  XHandle handle;

  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  if ( _this->Super1.bitmap != 0 )
  {
    XHandle handle = _this->Super1.bitmap;
    EwFreeBitmap((XBitmap*)handle );
    _this->Super1.bitmap = 0;
    _this->Super1.FrameSize = _Const0000;
    _this->Super1.FrameDelay = 0;
    _this->Super1.NoOfFrames = 1;
    _this->Super1.Animated = 0;
  }

  name = _this->Name;
  handle = 0;
  {
    extern XBitmap* EwLoadExternBitmap( XString aName );
    handle = (XHandle)EwLoadExternBitmap( name );
  }
  _this->Super1.bitmap = handle;

  if ( _this->Super1.bitmap != 0 )
  {
    XInt32 noOfFrames = 1;
    XPoint frameSize = _Const0000;
    XInt32 frameDelay = 0;
    handle = _this->Super1.bitmap;
    {
      XBitmap* bmp = (XBitmap*)handle;

      noOfFrames = bmp->NoOfVirtFrames;
      frameSize  = bmp->FrameSize;
      frameDelay = bmp->FrameDelay;
    }
    _this->Super1.NoOfFrames = noOfFrames;
    _this->Super1.FrameSize = frameSize;
    _this->Super1.FrameDelay = frameDelay;
    _this->Super1.Animated = (XBool)(( _this->Super1.FrameDelay > 0 ) && ( _this->Super1.NoOfFrames 
    > 1 ));
  }

  EwNotifyObjObservers((XObject)_this, 0 );
}

/* Variants derived from the class : 'Resources::ExternBitmap' */
EW_DEFINE_CLASS_VARIANTS( ResourcesExternBitmap )
EW_END_OF_CLASS_VARIANTS( ResourcesExternBitmap )

/* Virtual Method Table (VMT) for the class : 'Resources::ExternBitmap' */
EW_DEFINE_CLASS( ResourcesExternBitmap, ResourcesBitmap, Name, Name, Name, Name, 
                 Name, _.VMT, "Resources::ExternBitmap" )
  ResourcesBitmap_OnSetFrameSize,
  ResourcesBitmap_Update,
EW_END_OF_CLASS( ResourcesExternBitmap )

/* Initializer for the class 'Resources::Font' */
void ResourcesFont__Init( ResourcesFont _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  CoreResource__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ResourcesFont );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ResourcesFont );

  /* Call the user defined constructor */
  ResourcesFont_Init( _this, aArg );
}

/* Re-Initializer for the class 'Resources::Font' */
void ResourcesFont__ReInit( ResourcesFont _this )
{
  /* At first re-initialize the super class ... */
  CoreResource__ReInit( &_this->_.Super );
}

/* Finalizer method for the class 'Resources::Font' */
void ResourcesFont__Done( ResourcesFont _this )
{
  /* Call the user defined destructor of the class */
  ResourcesFont_Done( _this );

  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( CoreResource );

  /* Don't forget to deinitialize the super class ... */
  CoreResource__Done( &_this->_.Super );
}

/* 'C' function for method : 'Resources::Font.Done()' */
void ResourcesFont_Done( ResourcesFont _this )
{
  ResourcesFont_freeFont( _this );
}

/* 'C' function for method : 'Resources::Font.Init()' */
void ResourcesFont_Init( ResourcesFont _this, XHandle aArg )
{
  ResourcesFont_loadFont( _this, aArg );
}

/* 'C' function for method : 'Resources::Font.freeFont()' */
void ResourcesFont_freeFont( ResourcesFont _this )
{
  XHandle handle;

  if ( _this->font == 0 )
    return;

  handle = _this->font;
  EwFreeFont((XFont*)handle );
  _this->font = 0;
  _this->Ascent = 0;
  _this->Descent = 0;
  _this->Leading = 0;
}

/* 'C' function for method : 'Resources::Font.loadFont()' */
void ResourcesFont_loadFont( ResourcesFont _this, XHandle aFontResource )
{
  XHandle handle;
  XInt32 ascent;
  XInt32 descent;
  XInt32 leading;

  if ( aFontResource == 0 )
    return;

  handle = 0;
  ascent = 0;
  descent = 0;
  leading = 0;
  {
    /* aFontResource is a pointer to a memory where the font resource is stored. */
    XFont* font = EwLoadFont((const XFntRes*)aFontResource );

    /* After the font has been loaded query its ascent and descent. */
    if ( font )
    {
      ascent  = font->Ascent;
      descent = font->Descent;
      leading = font->Leading;
    }

    handle = (XHandle)(void*)font;
  }
  _this->font = handle;
  _this->Ascent = ascent;
  _this->Descent = descent;
  _this->Leading = leading;
}

/* 'C' function for method : 'Resources::Font.GetFlowTextAdvance()' */
XInt32 ResourcesFont_GetFlowTextAdvance( ResourcesFont _this, XString aFlowString )
{
  XHandle handle;
  XInt32 advance;

  if ( _this->font == 0 )
    return 0;

  handle = _this->font;
  advance = 0;
  advance = EwGetFlowTextAdvance((XFont*)handle, aFlowString );
  return advance;
}

/* 'C' function for method : 'Resources::Font.ParseFlowString()' */
XString ResourcesFont_ParseFlowString( ResourcesFont _this, XString aString, XInt32 
  aOffset, XInt32 aWidth, XInt32 aMaxNoOfRows, XHandle aBidi )
{
  XHandle handle;
  XString result;

  if ( aOffset < 0 )
    aOffset = 0;

  if (( _this->font == 0 ) || (( aOffset > 0 ) && ( aOffset >= EwGetStringLength( 
      aString ))))
    return 0;

  handle = _this->font;
  result = 0;
  result = EwParseFlowString((XFont*)handle, aString + aOffset, aWidth, aMaxNoOfRows, aBidi );
  return result;
}

/* The method GetTextAdvance() calculates the horizontal advance in pixel of a text 
   row to print with this font. This value is calculated by the sum of advance values 
   of all affected glyphs. The text is passed in the parameter aString. The parameter 
   aOffset determines within aString the sign to start the calculation. If aOffset 
   is zero, the calculation starts with the first sign. The parameter aCount determines 
   the max. number of following sigs to calculate the advance value. If aCount is 
   -1, all signs until the end of the string will be evaluated. */
XInt32 ResourcesFont_GetTextAdvance( ResourcesFont _this, XString aString, XInt32 
  aOffset, XInt32 aCount )
{
  XHandle handle;
  XInt32 advance;

  if ( aOffset < 0 )
    aOffset = 0;

  if (( _this->font == 0 ) || (( aOffset > 0 ) && ( aOffset >= EwGetStringLength( 
      aString ))))
    return 0;

  handle = _this->font;
  advance = 0;
  advance = EwGetTextAdvance((XFont*)handle, aString + aOffset, aCount );
  return advance;
}

/* Variants derived from the class : 'Resources::Font' */
EW_DEFINE_CLASS_VARIANTS( ResourcesFont )
EW_END_OF_CLASS_VARIANTS( ResourcesFont )

/* Virtual Method Table (VMT) for the class : 'Resources::Font' */
EW_DEFINE_CLASS( ResourcesFont, CoreResource, _.VMT, _.VMT, _.VMT, _.VMT, _.VMT, 
                 _.VMT, "Resources::Font" )
EW_END_OF_CLASS( ResourcesFont )

/* Include a file containing the bitmap resource : 'Resources::WhiteBitmapStripe' */
#include "_ResourcesWhiteBitmapStripe.h"

/* Table with links to derived variants of the bitmap resource : 'Resources::WhiteBitmapStripe' */
EW_RES_WITHOUT_VARIANTS( ResourcesWhiteBitmapStripe )

/* Embedded Wizard */
