#include "wx/ledBarGraph/ledBarGraph.h"
BEGIN_EVENT_TABLE(wxLedBarGraph, wxControl)
	EVT_PAINT(wxLedBarGraph::OnPaint)
	EVT_ERASE_BACKGROUND(wxLedBarGraph::OnEraseBackGround)
	EVT_SIZE( wxLedBarGraph::OnResize )
END_EVENT_TABLE()

IMPLEMENT_DYNAMIC_CLASS(wxLedBarGraph, wxControl)

wxLedBarGraph::~wxLedBarGraph(void)
{
}

bool wxLedBarGraph::Create(wxWindow* parent, wxWindowID id,
		const wxPoint& pos, const wxSize& size, long style,
		const wxValidator& validator)
{
	if (!wxControl::Create(parent, id, pos, size, style, validator)){
		return false;
	}

	SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOW ) );

	//m_fontData.SetInitialFont(GetFont());
	//m_fontData.SetChosenFont(GetFont());
	//m_fontData.SetColour(GetForegroundColour());

	//this->SetMinSize(  wxSize(100, 25) );

	// Tell the sizers to use the given or best size
//	SetBestFittingSize(size);
	return true;
}
void wxLedBarGraph::OnEraseBackGround(wxEraseEvent& myEvent)
{
};

void wxLedBarGraph::OnResize( wxSizeEvent& evt )
{
    wxRect rect = GetClientRect();

    if( m_sizingMode == ledBG_FIXED_N_BARS ){
        if( m_orientation == ledBG_ORIENT_HORIZONTAL ){
            m_barWidths = (rect.width/m_nBars);
        }else{
            m_barWidths = (rect.height/m_nBars);
        }
        if( m_barWidths < 6 ){
            //things less than 6 dont look that good, so you get a black box.
            return;
        }
    }else{
        if( m_orientation == ledBG_ORIENT_HORIZONTAL ){
            m_nBars = rect.width / m_barWidths;
        }else{
            m_nBars = rect.height / m_barWidths;
        }

        if( (m_nBars % 2) == 1 ){
            m_nBars--;
        }
    }

    //this figures out the gutters.  because of how i calculate width and how I draw the rects,
	//there is some error that I center in the control...
    if( m_orientation == ledBG_ORIENT_HORIZONTAL ){
        m_startX = (rect.width - ( m_nBars * m_barWidths))/2 ;
    }else{
        m_startX = (rect.height - ( m_nBars * m_barWidths))/2 ;
    }

	Refresh();
}

/*
I can't say I'm super happy with this function yet.
There is still a lot of stuff in here that should not be recomputued on every paint or every paint
call.  However, it is a bit easier to understand what is happening and debug problems with it
written this way
*/
void wxLedBarGraph::OnPaint( wxPaintEvent& evt )
{
	wxBufferedPaintDC dc(this);
	wxRect rect = GetClientRect();

	//colors
	wxBrush blackBrush = wxBrush( wxColour( _("black") ) );
	wxColor red =  wxColour( _("red") );
	wxColor green =  wxColour( _("green") );
	wxColor yellow =  wxColour( _("yellow") );
    wxColor tmpColor;

    int cntr =  m_nBars / 2;

    int minG=0;// = -1;
    int maxG=0;// =  (m_nBars / 4);

    int minY= -1 ;
    int maxY= 1;

    if( m_mode == ledBG_DOUBLE_SIDED ){
        minG = cntr - (m_nBars / 8);
        maxG = cntr + (m_nBars / 8);

        minY = cntr - 3*(m_nBars / 8);
        maxY = cntr + 3*(m_nBars / 8);
    }else if( m_mode == ledBG_SINGLE_SIDED_TOP_LEFT){
        minG = -1;
        maxG =  (m_nBars / 4);

        minY = (m_nBars / 4) -1 ;
        maxY = 3*(m_nBars / 4);
    }else if( m_mode == ledBG_SINGLE_SIDED_BOTTOM_RIGHT){
        minG = 3*(m_nBars / 4) ;
        maxG =  m_nBars;

        minY = (m_nBars / 4) -1 ;
        maxY = 3*(m_nBars / 4);
    }



    int X = m_startX;

	//draw a black box for the first (left) gutter.
	dc.SetBrush( blackBrush );
    if( m_orientation == ledBG_ORIENT_HORIZONTAL ){
        dc.DrawRectangle(0, 0, X, rect.height);
    }else{
        dc.DrawRectangle(0, 0, rect.width, X);
    }

	int thold = 0;
    int i;
	for( i = 0; i < m_nBars; i++ ){
        //double dim = .7;
        bool maxedOut = false;
        bool drawMe = false;

        if( m_mode == ledBG_DOUBLE_SIDED ){
            if( m_value < 0  ){
                thold = (int)(( m_nBars / 2 ) - ( fabs(m_value) * ( m_nBars / 2 )));
                drawMe = (i >= thold) && ( i <= ( m_nBars / 2 ) );

                if( m_value > -1 ){
                    maxedOut = false;
                }else{
                    maxedOut = true;
                }
            }else if(	m_value==0 ){
                drawMe = (i == m_nBars/2);
                maxedOut = true;
            }else if(m_value > 0 ) {
                thold = (int)(( m_nBars / 2 ) + ( fabs(m_value) * ( m_nBars / 2 ) + 1));
                drawMe = (i <= thold) && ( i >= ( m_nBars / 2 ) );

                if( m_value < 1 ){
                    maxedOut = false;
                }else{
                    maxedOut = true;
                }
            }else{
                //this state should be unreachable
                drawMe = false;
            }

        }else if( m_mode == ledBG_SINGLE_SIDED_TOP_LEFT ){
            if( m_value <= -1  ){
                if( i == 0){
                    maxedOut = true;
                    drawMe = true;//( i <= m_nBars );
                }
            }else if( m_value >= 1 ){
                maxedOut = (i== m_nBars - 1);
                drawMe = true;
            }else{
                maxedOut = false;
                thold = (int)(m_nBars - (( m_nBars / 2 ) + ( - m_value * ( m_nBars/2 ))));
                drawMe = (i <= thold) ;
            }
        }else if( m_mode == ledBG_SINGLE_SIDED_BOTTOM_RIGHT ){
            if( m_value <= -1  ){
                if( i == m_nBars-1 ){
                    drawMe = true;
                    maxedOut = true;
                }
            }else if( m_value >= 1 ){
                maxedOut = (i==0);//true;
                drawMe = true;
            }else{
                maxedOut = false;
                thold = (int)(( m_nBars / 2 ) + ( - m_value * ( m_nBars/2 )));
                drawMe = (i >= thold) ;
            }
        }

        //Id like to abstract out the color eventually
		if( i <= maxG && i >= minG ) {
			tmpColor = green;
		}else if ( i < maxY && i > minY){
            tmpColor = yellow;
		}else{
			tmpColor = red;
		}

        double dim=0;
		//regular on
		if( ! drawMe ){
			//led off
			dim = .15;
		}else if (  maxedOut && (i == m_nBars -1 || i == 0) || (i == m_nBars/2) && m_mode == ledBG_DOUBLE_SIDED ) {
            //max it out, dude!
            dim = 1;
        }else{
            dim =.7;
        };

		unsigned char r = tmpColor.Red();
		unsigned char g = tmpColor.Green();
		unsigned char b = tmpColor.Blue();
		tmpColor = wxColour(  (int) (r * dim), (int) (g* dim), (int) (b* dim) );
		dc.SetBrush( wxBrush( tmpColor ) );

        if( m_orientation == ledBG_ORIENT_HORIZONTAL ){
            dc.DrawRectangle(X, 0, X + m_barWidths, rect.height);
        }else{
            dc.DrawRectangle(0, X,  rect.width, X + m_barWidths);
        }

		//increment to the next bar
		X += m_barWidths;
	}

	//draw the black gutter on the right edge
	dc.SetBrush( blackBrush );

    if( m_orientation == ledBG_ORIENT_HORIZONTAL ){
        dc.DrawRectangle(X, 0,rect.width , rect.height);
    }else{
        dc.DrawRectangle(0, X, rect.height, rect.width);
    }
}



void wxLedBarGraph::SetMaxValue( double val )
{
	m_maxVal = val;
	RescaleValues();
}

void wxLedBarGraph::SetMinValue( double val )
{
	m_minVal = val;
	RescaleValues();
}

void wxLedBarGraph::SetValue( double val )
{
    m_realValue = val;
    RescaleValues();
}

void wxLedBarGraph::SetNBars( int nBars )
{
    m_nBars = nBars;

    wxSizeEvent b;
    OnResize(b);
}
void wxLedBarGraph::SetBarWidths( int width )
{
    m_barWidths = width;

    wxSizeEvent b;
    OnResize(b);
}


void wxLedBarGraph::SetSizingMode( ledBGSizeMode mode )
{
    m_sizingMode = mode;

    wxSizeEvent a;
    OnResize(a);
}

void wxLedBarGraph::SetDrawingMode( ledBGDrawMode mode )
{
    m_mode = mode;

    wxSizeEvent a;
    OnResize(a);
}

void wxLedBarGraph::SetOrientation( ledBGOrient orient )
{
    m_orientation = orient;

   // InvalidateBestSize();

    wxSizeEvent a;
    OnResize(a);
}














