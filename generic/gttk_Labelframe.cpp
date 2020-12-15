/*
 *  gttk_Labelframe.cpp
 * -----------------------
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

#if 0
/*
 * Map between Tk/Tile & Gtk/GNOME state flags.
 */
static Ttk_StateTable labelframe_statemap[] =
{
};
#endif

typedef struct {
} LabelframeBorderElement;


static Ttk_ElementOptionSpec LabelframeBorderElementOptions[] = {
    {NULL}
};

static void LabelframeBorderElementGeometry(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    int *widthPtr, int *heightPtr, Ttk_Padding *paddingPtr)
{
    *paddingPtr = Ttk_UniformPadding(LabelframeUniformPadding);
}

static void LabelframeBorderElementDraw(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    Drawable d, Ttk_Box b, unsigned state)
{
    GTTK_GTK_DRAWABLE_DEFINITIONS;
    GTTK_ENSURE_GTK_STYLE_ENGINE_ACTIVE;
    /* GTTK_SETUP_GTK_DRAWABLE; */
    GtkWidget *widget = gttk_GetFrame(wc);
    GTTK_ENSURE_WIDGET_OK;
    GTTK_STYLE_FROM_WIDGET;
    GTTK_DRAWABLE_FROM_WIDGET;
    // GTTK_ATTACH_STYLE_TO_WIDGET;
    // GTTK_SETUP_WIDGET_SIZE(b.width, b.height);
    // GTTK_WIDGET_SET_FOCUS(widget);
    GTTK_DEFAULT_BACKGROUND;
    // gtk_paint_flat_box(style, gdkDrawable, gtkState, gtkShadow, NULL,
    //                            widget, "frame", 0, 0, b.width, b.height);
    gttk_CopyGtkPixmapOnToDrawable(gdkDrawable, d, tkwin,
                   0, 0, b.width, b.height, 0, 0);
    gttk_StateShadowTableLookup(NULL, state, gtkState, gtkShadow,
            GTTK_SECTION_BUTTONS|GTTK_SECTION_ALL);
    gtk_paint_shadow(style, gdkDrawable, gtkState, gtkShadow, NULL, widget,
                     "frame", 0, 0, b.width, b.height);
    gttk_CopyGtkPixmapOnToDrawable(gdkDrawable, d, tkwin,
                   0, 0, b.width, b.height, b.x, b.y);
    GTTK_CLEANUP_GTK_DRAWABLE;
}

static Ttk_ElementSpec LabelframeBorderElementSpec = {
    TK_STYLE_VERSION_2,
    sizeof(LabelframeBorderElement),
    LabelframeBorderElementOptions,
    LabelframeBorderElementGeometry,
    LabelframeBorderElementDraw
};

/*------------------------------------------------------------------------
 * +++ Widget layout.
 */

TTK_BEGIN_LAYOUT(LabelframeLayout)
    /* Note: labelframe widget does its own layout */
    TTK_NODE("Labelframe.border", TTK_FILL_BOTH)
TTK_END_LAYOUT

int gttk_Init_Labelframe(Tcl_Interp *interp,
                       gttk_WidgetCache **wc, Ttk_Theme themePtr)
{
    /*
     * Register elements:
     */
    Ttk_RegisterElement(interp, themePtr, "Labelframe.border",
            &LabelframeBorderElementSpec, (void *) wc[0]);
    
    /*
     * Register layouts:
     */
    Ttk_RegisterLayout(themePtr, "TLabelframe", LabelframeLayout);

    return TCL_OK;
}; /* gttk_Init_Labelframe */
