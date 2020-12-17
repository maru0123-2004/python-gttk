/*
 *  gttk_Separator.cpp
 * ---------------------
 *
 * This file is part of the gttk package, a Tk/Tile based theme that uses
 * Gtk/GNOME for drawing.
 *
 * Copyright (C) 2004-2008 by:
 * Georgios Petasis, petasis@iit.demokritos.gr,
 * Software and Knowledge Engineering Laboratory,
 * Institute of Informatics and Telecommunications,
 * National Centre for Scientific Research (NCSR) "Demokritos",
 * Aghia Paraskevi, 153 10, Athens, Greece.
 */
#include "gttk_Utilities.h"
#include "gttk_TkHeaders.h"
#include "gttk_WidgetDefaults.h"

static Ttk_StateTable separator_statemap[] = {
};

typedef struct {
  Tcl_Obj* orientObj;
  Tcl_Obj* borderObj;
} SeparatorElement;

static Ttk_ElementOptionSpec SeparatorElementOptions[] = {
    {"-orient", TK_OPTION_ANY, Tk_Offset(SeparatorElement, orientObj), "horizontal"},
    {"-background", TK_OPTION_BORDER, Tk_Offset(SeparatorElement, borderObj), DEFAULT_BACKGROUND},
    {NULL}
};

static void SeparatorElementGeometry(
    void* clientData, void* elementRecord, Tk_Window tkwin,
    int* widthPtr, int* heightPtr, Ttk_Padding* paddingPtr) {
  GTTK_WIDGET_CACHE_DEFINITION;
  GTTK_ENSURE_GTK_STYLE_ENGINE_ACTIVE;
  GtkWidget* widget = gttk_GetSeparator(wc);
  GTTK_ENSURE_WIDGET_OK;
} // SeparatorElementGeometry

static void SeparatorElementDraw(
    void* clientData, void* elementRecord, Tk_Window tkwin,
    Drawable d, Ttk_Box b, unsigned state) {
  GTTK_GTK_DRAWABLE_DEFINITIONS;
  GTTK_ENSURE_GTK_STYLE_ENGINE_ACTIVE;
  GtkWidget* widget = gttk_GetSeparator(wc);
  GTTK_ENSURE_WIDGET_OK;
  GTTK_STYLE_FROM_WIDGET;
  GTTK_DRAWABLE_FROM_WIDGET;

  gint height, width;
  gtk_widget_style_get(widget, "separator-height", &height, "separator-width", &width, NULL);

  gttk_CopyGtkPixmapOnToDrawable(gdkDrawable, d, tkwin, 0, 0, b.width, b.height, b.x, b.y);
  Tcl_MutexUnlock(&gttkMutex);
} // SeparatorElementDraw

static void GeneralSeparatorElementGeometry(
    void* clientData, void* elementRecord, Tk_Window tkwin,
    int* widthPtr, int* heightPtr, Ttk_Padding* paddingPtr) {
  gttk_WidgetCache** wc = (gttk_WidgetCache**) clientData;
  if (wc == NULL)
    return;
  SeparatorElement* separator = (SeparatorElement*) elementRecord;
  int orient;
  Ttk_GetOrientFromObj(NULL, separator->orientObj, &orient);
  switch (orient) {
    case TTK_ORIENT_HORIZONTAL:
      SeparatorElementGeometry((void*) wc[0], elementRecord, tkwin, widthPtr, heightPtr, paddingPtr);
      break;
    case TTK_ORIENT_VERTICAL:
      SeparatorElementGeometry((void*) wc[1], elementRecord, tkwin, widthPtr, heightPtr, paddingPtr);
      break;
  }
} // GeneralSeparatorElementGeometry

static void GeneralSeparatorElementDraw(
    void* clientData, void* elementRecord, Tk_Window tkwin,
    Drawable d, Ttk_Box b, unsigned state) {
  gttk_WidgetCache** wc = (gttk_WidgetCache**) clientData;
  if (wc == NULL) return;
  SeparatorElement* separator = (SeparatorElement*) elementRecord;
  int orient;
  Ttk_GetOrientFromObj(NULL, separator->orientObj, &orient);
  switch (orient) {
    case TTK_ORIENT_HORIZONTAL:
      SeparatorElementDraw((void*) wc[0], elementRecord, tkwin, d, b, state);
      break;
    case TTK_ORIENT_VERTICAL:
      SeparatorElementDraw((void*) wc[1], elementRecord, tkwin, d, b, state);
      break;
  }
} // GeneralSeparatorElementDraw

static Ttk_ElementSpec SeparatorElementSpec = {
    TK_STYLE_VERSION_2,
    sizeof(SeparatorElement),
    SeparatorElementOptions,
    SeparatorElementGeometry,
    SeparatorElementDraw
}; // SeparatorElementSpec

static Ttk_ElementSpec GeneralSeparatorElementSpec = {
    TK_STYLE_VERSION_2,
    sizeof(SeparatorElement),
    SeparatorElementOptions,
    GeneralSeparatorElementGeometry,
    GeneralSeparatorElementDraw
}; // GeneralSeparatorElementSpec

// Widget layout
TTK_BEGIN_LAYOUT(SeparatorLayout)
        TTK_NODE("Separator.separator", TTK_FILL_BOTH)
TTK_END_LAYOUT

int gttk_Init_Separator(Tcl_Interp* interp, gttk_WidgetCache** wc, Ttk_Theme themePtr) {
  // Register elements
  Ttk_RegisterElement(interp, themePtr, "separator", &GeneralSeparatorElementSpec, (void*) wc);
  Ttk_RegisterElement(interp, themePtr, "hseparator", &SeparatorElementSpec, (void*) wc[0]);
  Ttk_RegisterElement(interp, themePtr, "vseparator", &SeparatorElementSpec, (void*) wc[1]);
  // Register layouts
  Ttk_RegisterLayout(themePtr, "TSeparator", SeparatorLayout);

  return TCL_OK;
}; // gttk_Init_Separator
