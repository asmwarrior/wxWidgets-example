/////////////////////////////////////////////////////////////////////////////
// Name:        mainframe.cpp
// Purpose:     Main window of the application
// Author:      Julian Smart
// Modified by: 
// Created:     03/26/05 12:36:16
// RCS-ID:      
// Copyright:   (c) Julian Smart
// Licence:     wxWindows License
/////////////////////////////////////////////////////////////////////////////

#if defined(__GNUG__) && !defined(__APPLE__)
#pragma implementation "mainframe.h"
#endif

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "wx/settings.h"

////@begin includes
////@end includes

#include "mainframe.h"
#include "browser.h"
#include "riffle.h"
#include "settings.h"
#include "symbols.h"

////@begin XPM images
#include "bitmaps/riffle32x32.xpm"
#include "bitmaps/zoomin.xpm"
#include "bitmaps/zoomout.xpm"
#include "bitmaps/fitwindow.xpm"
#include "bitmaps/actualsize.xpm"
#include "bitmaps/browse.xpm"
#include "bitmaps/copy.xpm"
////@end XPM images

/*!
 * RiffleFrame type definition
 */

IMPLEMENT_CLASS( RiffleFrame, wxFrame )

/*!
 * RiffleFrame event table definition
 */

BEGIN_EVENT_TABLE( RiffleFrame, wxFrame )
    EVT_TREE_SEL_CHANGED( wxID_TREECTRL, RiffleFrame::OnDirctrlSelChanged )

////@begin RiffleFrame event table entries
    EVT_CLOSE( RiffleFrame::OnCloseWindow )
    EVT_IDLE( RiffleFrame::OnIdle )

#if defined(__WXWINCE__)
    EVT_MENU( wxID_HELP_CONTENTS, RiffleFrame::OnHelpContentsClick )
#endif

#if defined(__WXWINCE__)
    EVT_MENU( wxID_ABOUT, RiffleFrame::OnAboutClick )
#endif

#if defined(__WXWINCE__)
    EVT_MENU( wxID_COPY, RiffleFrame::OnCopyClick )
    EVT_UPDATE_UI( wxID_COPY, RiffleFrame::OnCopyUpdate )
#endif

    EVT_MENU( wxID_EXIT, RiffleFrame::OnExitClick )

#if defined(__WXMAC__)
    EVT_MENU( wxID_CLOSE, RiffleFrame::OnCloseClick )
#endif

#if defined(__WXMSW_DESKTOP__) || defined(__WXMAC__) || defined(__WXGTK__)
    EVT_MENU( wxID_COPY, RiffleFrame::OnCopyClick )
    EVT_UPDATE_UI( wxID_COPY, RiffleFrame::OnCopyUpdate )
#endif

    EVT_MENU( ID_ZOOMIN, RiffleFrame::OnZoominClick )

    EVT_MENU( ID_ZOOMOUT, RiffleFrame::OnZoomoutClick )

    EVT_MENU( ID_ACTUALSIZE, RiffleFrame::OnActualsizeClick )
    EVT_UPDATE_UI( ID_ACTUALSIZE, RiffleFrame::OnActualsizeUpdate )

    EVT_MENU( ID_FITWINDOW, RiffleFrame::OnFitwindowClick )
    EVT_UPDATE_UI( ID_FITWINDOW, RiffleFrame::OnFitwindowUpdate )

    EVT_MENU( wxID_PREFERENCES, RiffleFrame::OnPreferencesClick )

#if defined(__WXMAC__) || defined(__WXGTK__) || defined(__WXMSW_DESKTOP__)
    EVT_MENU( wxID_HELP_CONTENTS, RiffleFrame::OnHelpContentsClick )
#endif

#if defined(__WXMSW_DESKTOP__) || defined(__WXMAC__) || defined(__WXGTK__)
    EVT_MENU( wxID_ABOUT, RiffleFrame::OnAboutClick )
#endif

#if defined(__WXMAC__)
    EVT_MENU( ID_ABOUT, RiffleFrame::OnMacAboutClick )
#endif

    EVT_MENU( ID_SHOWTHUMBNAILS, RiffleFrame::OnShowthumbnailsClick )
    EVT_UPDATE_UI( ID_SHOWTHUMBNAILS, RiffleFrame::OnShowthumbnailsUpdate )

////@end RiffleFrame event table entries

END_EVENT_TABLE()

/*!
 * RiffleFrame constructors
 */

RiffleFrame::RiffleFrame( )
{
}

RiffleFrame::RiffleFrame( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Create( parent, id, caption, pos, size, style );
}

/*!
 * RiffleFrame creator
 */

bool RiffleFrame::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
////@begin RiffleFrame member initialisation
    m_splitterWindow = NULL;
    m_dirCtrl = NULL;
    m_browserCtrl = NULL;
////@end RiffleFrame member initialisation

    m_selectionCount = -1;

    SetExtraStyle(GetExtraStyle()|wxFRAME_EX_METAL);

////@begin RiffleFrame creation
    wxFrame::Create( parent, id, caption, pos, size, style );

    CreateControls();
    SetIcon(GetIconResource(wxT("bitmaps/riffle32x32.png")));
////@end RiffleFrame creation
    return TRUE;
}

/*!
 * Control creation for RiffleFrame
 */

void RiffleFrame::CreateControls()
{    
////@begin RiffleFrame content construction
    // Generated by DialogBlocks, Apr 13 2005 (Personal Edition)

    RiffleFrame* itemFrame1 = this;

    wxMenuBar* menuBar = new wxMenuBar;
    wxMenu* itemMenu3 = new wxMenu;
#if defined(__WXWINCE__)
    itemMenu3->Append(wxID_HELP_CONTENTS, _("&Help Contents"), _("Shows the help contents"), wxITEM_NORMAL);
#endif
#if defined(__WXWINCE__)
    itemMenu3->Append(wxID_ABOUT, _("&About Riffle..."), _("Shows the About box"), wxITEM_NORMAL);
#endif
#if defined(__WXWINCE__)
    itemMenu3->AppendSeparator();
#endif
#if defined(__WXWINCE__)
    itemMenu3->Append(wxID_COPY, _("&Copy\tCtrl+C"), _("Copy image to the clipboard"), wxITEM_NORMAL);
#endif
#if defined(__WXWINCE__)
    itemMenu3->AppendSeparator();
#endif
    itemMenu3->Append(wxID_EXIT, _("E&xit\tAlt+F4"), _("Quits the application"), wxITEM_NORMAL);
#if defined(__WXMAC__)
    itemMenu3->Append(wxID_CLOSE, _("&Quit"), _("Quits the application"), wxITEM_NORMAL);
#endif
    menuBar->Append(itemMenu3, _("&File"));
#if defined(__WXMSW_DESKTOP__) || defined(__WXMAC__) || defined(__WXGTK__)
    wxMenu* itemMenu11 = new wxMenu;
#if defined(__WXMSW_DESKTOP__) || defined(__WXMAC__) || defined(__WXGTK__)
    itemMenu11->Append(wxID_COPY, _("&Copy\tCtrl+C"), _("Copy image to the clipboard"), wxITEM_NORMAL);
#endif
    menuBar->Append(itemMenu11, _("&Edit"));
#endif
    wxMenu* itemMenu13 = new wxMenu;
    itemMenu13->Append(ID_SHOWTHUMBNAILS, _("Show &Thumbnails\tCtrl+T"), _("Shows thumbnails"), wxITEM_CHECK);
    itemMenu13->AppendSeparator();
    itemMenu13->Append(ID_ZOOMIN, _("Zoom &In\t+"), _("Zooms in"), wxITEM_NORMAL);
    itemMenu13->Append(ID_ZOOMOUT, _("Zoom &Out\t-"), _("Zooms out"), wxITEM_NORMAL);
    itemMenu13->Append(ID_ACTUALSIZE, _("&Actual Size\tCtrl+S"), _("Shows image actual size"), wxITEM_CHECK);
    itemMenu13->Append(ID_FITWINDOW, _("&Fit Window\tCtrl+F"), _("Fits image to window"), wxITEM_CHECK);
#if defined(__WXMSW__) || defined(__WXGTK__)
    itemMenu13->AppendSeparator();
#endif
    itemMenu13->Append(wxID_PREFERENCES, _("&Settings...\tCtrl+P"), _("Shows the settings dialog"), wxITEM_NORMAL);
    menuBar->Append(itemMenu13, _("&View"));
#if defined(__WXMSW_DESKTOP__) || defined(__WXMAC__) || defined(__WXGTK__)
    wxMenu* itemMenu22 = new wxMenu;
#if defined(__WXMAC__) || defined(__WXGTK__) || defined(__WXMSW_DESKTOP__)
    itemMenu22->Append(wxID_HELP_CONTENTS, _("&Help Contents"), _("Shows the help contents"), wxITEM_NORMAL);
#endif
#if defined(__WXMSW_DESKTOP__) || defined(__WXMAC__) || defined(__WXGTK__)
    itemMenu22->AppendSeparator();
#endif
#if defined(__WXMSW_DESKTOP__) || defined(__WXMAC__) || defined(__WXGTK__)
    itemMenu22->Append(wxID_ABOUT, _("&About Riffle..."), _("Shows the About box"), wxITEM_NORMAL);
#endif
#if defined(__WXMAC__)
    itemMenu22->Append(ID_ABOUT, _("&About Riffle..."), _("Shows the About box"), wxITEM_NORMAL);
#endif
    menuBar->Append(itemMenu22, _("&Help"));
#endif
    itemFrame1->SetMenuBar(menuBar);

    wxToolBar* itemToolBar27 = CreateToolBar( wxTB_FLAT|wxTB_HORIZONTAL, ID_TOOLBAR );
    itemToolBar27->SetToolBitmapSize(wxSize(16, 16));
    wxBitmap itemtool28Bitmap(itemFrame1->GetBitmapResource(wxT("bitmaps/zoomin.png")));
    itemToolBar27->AddTool(ID_ZOOMIN, _T(""), itemtool28Bitmap, _("Zoom in"), wxITEM_NORMAL);
    wxBitmap itemtool29Bitmap(itemFrame1->GetBitmapResource(wxT("bitmaps/zoomout.png")));
    itemToolBar27->AddTool(ID_ZOOMOUT, _T(""), itemtool29Bitmap, _("Zoom out"), wxITEM_NORMAL);
    wxBitmap itemtool30Bitmap(itemFrame1->GetBitmapResource(wxT("bitmaps/fitwindow.png")));
    itemToolBar27->AddTool(ID_FITWINDOW, _T(""), itemtool30Bitmap, _("Fit to window"), wxITEM_CHECK);
    wxBitmap itemtool31Bitmap(itemFrame1->GetBitmapResource(wxT("bitmaps/actualsize.png")));
    itemToolBar27->AddTool(ID_ACTUALSIZE, _T(""), itemtool31Bitmap, _("Actual size"), wxITEM_CHECK);
    wxBitmap itemtool32Bitmap(itemFrame1->GetBitmapResource(wxT("bitmaps/browse.png")));
    itemToolBar27->AddTool(ID_SHOWTHUMBNAILS, _T(""), itemtool32Bitmap, _("Show thumbnails"), wxITEM_CHECK);
    wxBitmap itemtool33Bitmap(itemFrame1->GetBitmapResource(wxT("bitmaps/copy.png")));
    itemToolBar27->AddTool(wxID_COPY, _T(""), itemtool33Bitmap, _("Copy image"), wxITEM_NORMAL);
    itemToolBar27->Realize();
    itemFrame1->SetToolBar(itemToolBar27);

    m_splitterWindow = new wxSplitterWindow( itemFrame1, ID_SPLITTERWINDOW, wxDefaultPosition, wxSize(100, 100), wxSP_3DBORDER|wxSP_3DSASH|wxSP_NO_XP_THEME|wxNO_BORDER );

    m_dirCtrl = new wxGenericDirCtrl( m_splitterWindow, ID_DIRCTRL, _T(""), wxDefaultPosition, wxDefaultSize, wxDIRCTRL_DIR_ONLY|wxNO_BORDER, _T("All files (*.*)|*.*"), 0 );

    m_browserCtrl = new RiffleBrowserViewer( m_splitterWindow, ID_THUMBNAILS, wxDefaultPosition, wxDefaultSize, wxNO_BORDER|wxTAB_TRAVERSAL );

    m_splitterWindow->SplitVertically(m_dirCtrl, m_browserCtrl, 50);

    wxStatusBar* itemStatusBar37 = new wxStatusBar( itemFrame1, ID_STATUSBAR, wxST_SIZEGRIP|wxNO_BORDER );
    itemStatusBar37->SetFieldsCount(2);
    itemFrame1->SetStatusBar(itemStatusBar37);

////@end RiffleFrame content construction

    m_splitterWindow->SetMinimumPaneSize(20);
    
    int sashPos = 100;
    wxGetApp().GetConfig()->Read(wxT("Window/SashPos"), & sashPos);
    m_splitterWindow->SetSashPosition(sashPos);

    int scale = 100;
    wxGetApp().GetConfig()->Read(wxT("General/Scale"), & scale);
    m_browserCtrl->GetImageViewerWindow()->SetScale(scale);

    UpdateThumbnailSize();

    wxString currentPath;
    bool restoreDir = true;
    wxGetApp().GetConfig()->Read(wxT("General/CurrentPath"), & currentPath);
    wxGetApp().GetConfig()->Read(wxT("General/RestoreLastPath"), & restoreDir);
    if (!currentPath.IsEmpty() && restoreDir)
    {
        m_dirCtrl->SetPath(currentPath);
    }

    CheckOrientation();
}

void RiffleFrame::UpdateThumbnailSize()
{    
    int thumbnailSize = 50;
    wxGetApp().GetConfig()->Read(wxT("General/ThumbnailSize"), & thumbnailSize);
    m_browserCtrl->GetThumbnailCtrl()->SetThumbnailImageSize(wxSize(thumbnailSize, thumbnailSize));
}

/// Changes orientation if necessary
void RiffleFrame::CheckOrientation()
{
    int screenWidth = wxSystemSettings::GetMetric(wxSYS_SCREEN_X);
    int screenHeight = wxSystemSettings::GetMetric(wxSYS_SCREEN_Y);

    int orient = wxHORIZONTAL;
    if (screenHeight > screenWidth)
        orient = wxVERTICAL;

    int splitMode = m_splitterWindow->GetSplitMode();
    int sashPos = m_splitterWindow->GetSashPosition();

    // If screen orientation is horizontal, want to split vertically (the norm)
    if (orient == wxHORIZONTAL && splitMode == wxSPLIT_HORIZONTAL)
    {
        m_splitterWindow->Unsplit();
        m_splitterWindow->SplitVertically(m_dirCtrl, m_browserCtrl, sashPos);
    }
    else if (orient == wxVERTICAL && splitMode == wxSPLIT_VERTICAL)
    {
        m_splitterWindow->Unsplit();
        m_splitterWindow->SplitHorizontally(m_dirCtrl, m_browserCtrl, sashPos);
    }
}

/*!
 * Should we show tooltips?
 */

bool RiffleFrame::ShowToolTips()
{
    return TRUE;
}

/*!
 * Get bitmap resources
 */

wxBitmap RiffleFrame::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin RiffleFrame bitmap retrieval
    if (name == wxT("bitmaps/zoomin.png"))
    {
        wxBitmap bitmap(zoomin_xpm);
        return bitmap;
    }
    else if (name == wxT("bitmaps/zoomout.png"))
    {
        wxBitmap bitmap(zoomout_xpm);
        return bitmap;
    }
    else if (name == wxT("bitmaps/fitwindow.png"))
    {
        wxBitmap bitmap(fitwindow_xpm);
        return bitmap;
    }
    else if (name == wxT("bitmaps/actualsize.png"))
    {
        wxBitmap bitmap(actualsize_xpm);
        return bitmap;
    }
    else if (name == wxT("bitmaps/browse.png"))
    {
        wxBitmap bitmap(browse_xpm);
        return bitmap;
    }
    else if (name == wxT("bitmaps/copy.png"))
    {
        wxBitmap bitmap(copy_xpm);
        return bitmap;
    }
    return wxNullBitmap;
////@end RiffleFrame bitmap retrieval
}

/*!
 * Get icon resources
 */

wxIcon RiffleFrame::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin RiffleFrame icon retrieval
    if (name == wxT("bitmaps/riffle32x32.png"))
    {
        wxIcon icon(riffle32x32_xpm);
        return icon;
    }
    return wxNullIcon;
////@end RiffleFrame icon retrieval
}

/*!
 * wxEVT_COMMAND_TREE_SEL_CHANGED event handler for wxID_TREECTRL
 */

void RiffleFrame::OnDirctrlSelChanged( wxTreeEvent& event )
{
    if (!m_browserCtrl || !m_browserCtrl->GetThumbnailCtrl())
        return;
        
    m_selectionCount ++;

    if (m_selectionCount > 1)
    {
        m_selectionCount --;
        return;
    }

    wxTreeItemId id = event.GetItem();
    if (id)
    {
        wxDirItemData* data = (wxDirItemData*) m_dirCtrl->GetTreeCtrl()->GetItemData(id);
        if (data && data->m_isDir)
        {
            m_browserCtrl->ShowFolder(data->m_path);
        }
    }

    m_selectionCount --;
}


/*!
 * wxEVT_COMMAND_MENU_SELECTED event handler for ID_ZOOMIN
 */

void RiffleFrame::OnZoominClick( wxCommandEvent& event )
{
    int zoomInc = 10;
    wxGetApp().GetConfig()->Read(wxT("General/ZoomIncrement"), & zoomInc);

    m_browserCtrl->GetImageViewerWindow()->Zoom(true, zoomInc);
}

/*!
 * wxEVT_COMMAND_MENU_SELECTED event handler for ID_ZOOMOUT
 */

void RiffleFrame::OnZoomoutClick( wxCommandEvent& event )
{
    int zoomInc = 10;
    wxGetApp().GetConfig()->Read(wxT("General/ZoomIncrement"), & zoomInc);

    m_browserCtrl->GetImageViewerWindow()->Zoom(false, zoomInc);
}

/*!
 * wxEVT_COMMAND_MENU_SELECTED event handler for ID_ACTUALSIZE
 */

void RiffleFrame::OnActualsizeClick( wxCommandEvent& event )
{
    m_browserCtrl->GetImageViewerWindow()->ZoomActualSize();
}

/*!
 * wxEVT_UPDATE_UI event handler for ID_ACTUALSIZE
 */

void RiffleFrame::OnActualsizeUpdate( wxUpdateUIEvent& event )
{
    if (m_browserCtrl && m_browserCtrl->GetImageViewerWindow()->GetScale() != 100)
        event.Check(m_browserCtrl->GetImageViewerWindow()->GetScale() == 100);
}

/*!
 * wxEVT_COMMAND_MENU_SELECTED event handler for ID_FITWINDOW
 */

void RiffleFrame::OnFitwindowClick( wxCommandEvent& event )
{
    if (m_browserCtrl->GetImageViewerWindow()->GetScale() != 0)
        m_browserCtrl->GetImageViewerWindow()->ZoomFitToWindow();
}

/*!
 * wxEVT_UPDATE_UI event handler for ID_FITWINDOW
 */

void RiffleFrame::OnFitwindowUpdate( wxUpdateUIEvent& event )
{
    event.Check(m_browserCtrl && m_browserCtrl->GetImageViewerWindow()->GetScale() == 0);
}


/*!
 * wxEVT_COMMAND_MENU_SELECTED event handler for ID_SHOWTHUMBNAILS
 */

void RiffleFrame::OnShowthumbnailsClick( wxCommandEvent& event )
{
    m_browserCtrl->ShowThumbnails(!m_browserCtrl->ShowingThumbnails());
}

/*!
 * wxEVT_UPDATE_UI event handler for ID_SHOWTHUMBNAILS
 */

void RiffleFrame::OnShowthumbnailsUpdate( wxUpdateUIEvent& event )
{
    event.Check(m_browserCtrl && m_browserCtrl->ShowingThumbnails());
}


/*!
 * wxEVT_COMMAND_MENU_SELECTED event handler for wxID_COPY
 */

void RiffleFrame::OnCopyClick( wxCommandEvent& event )
{
    m_browserCtrl->GetImageViewerWindow()->CopyToClipboard();
}

/*!
 * wxEVT_UPDATE_UI event handler for wxID_COPY
 */

void RiffleFrame::OnCopyUpdate( wxUpdateUIEvent& event )
{
    event.Enable(m_browserCtrl && m_browserCtrl->GetImageViewerWindow()->HasImage());
}


/*!
 * wxEVT_COMMAND_MENU_SELECTED event handler for wxID_HELP_CONTENTS
 */

void RiffleFrame::OnHelpContentsClick( wxCommandEvent& event )
{
    wxGetApp().ShowHelp();
}


#if defined(__WXMAC__)
/*!
 * wxEVT_COMMAND_MENU_SELECTED event handler for wxID_ABOUT
 * This is required to put an About menu item on the Help menu
 * as well as having it on the application menu on Mac.
 */

void RiffleFrame::OnMacAboutClick( wxCommandEvent& event )
{
    OnAboutClick(event);
}
#endif

/*!
 * wxEVT_COMMAND_MENU_SELECTED event handler for wxID_ABOUT
 */

void RiffleFrame::OnAboutClick( wxCommandEvent& event )
{
    wxString msg = wxString::Format(wxT("Riffle %.1f (c) Julian Smart\nA little image browser app"), rfVERSION_NUMBER);
    wxMessageBox(msg, wxT("About Riffle"), wxOK);
}


/*!
 * wxEVT_CLOSE_WINDOW event handler for ID_FRAME
 */

void RiffleFrame::OnCloseWindow( wxCloseEvent& event )
{
    if (!IsIconized() && !IsMaximized())
    {
        wxRect rect = GetRect();
        wxGetApp().GetConfig()->Write(wxT("Window/FrameX"), rect.x);
        wxGetApp().GetConfig()->Write(wxT("Window/FrameY"), rect.y);
        wxGetApp().GetConfig()->Write(wxT("Window/FrameWidth"), rect.width);
        wxGetApp().GetConfig()->Write(wxT("Window/FrameHeight"), rect.height);
    }
#if 0
    if (IsMaximized())
        pmGetProjectManager().SetMainWindowStatus(pmSHOW_STATUS_MAXIMIZED) ;
    else if (IsIconized())
        pmGetProjectManager().SetMainWindowStatus(pmSHOW_STATUS_MINIMIZED) ;
    else
        pmGetProjectManager().SetMainWindowStatus(pmSHOW_STATUS_NORMAL) ;
#endif
    if (m_splitterWindow->IsSplit())
         wxGetApp().GetConfig()->Write(wxT("Window/SashPos"), m_splitterWindow->GetSashPosition());
         
    wxGetApp().GetConfig()->Write(wxT("General/Scale"), m_browserCtrl->GetImageViewerWindow()->GetScale());
    wxGetApp().GetConfig()->Write(wxT("General/CurrentPath"), m_dirCtrl->GetPath());
    
    this->Destroy();
}


/*!
 * wxEVT_COMMAND_MENU_SELECTED event handler for ID_SETTINGS
 */

void RiffleFrame::OnPreferencesClick( wxCommandEvent& event )
{
    SettingsDialog settingsDialog(this);
    settingsDialog.ShowModal();
}


/*!
 * wxEVT_IDLE event handler for ID_FRAME
 */

void RiffleFrame::OnIdle( wxIdleEvent& event )
{
    // On devices where the orientation can change, we want to make
    // sure the splitter is the optimal orientation.
    CheckOrientation();
    event.Skip();
}


#if defined(__WXMAC__)
/*!
 * wxEVT_COMMAND_MENU_SELECTED event handler for wxID_CLOSE
 */

void RiffleFrame::OnCloseClick( wxCommandEvent& event )
{
    Close();
}
#endif


/*!
 * wxEVT_COMMAND_MENU_SELECTED event handler for wxID_EXIT
 */

void RiffleFrame::OnExitClick( wxCommandEvent& event )
{
    Close();
}

