/***************************************************************************
 *   Copyright 2005-2008 Last.fm Ltd.                                      *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Steet, Fifth Floor, Boston, MA  02110-1301, USA.          *
 ***************************************************************************/

#include "SeedDelegate.h"

SeedDelegate::SeedDelegate( QObject* parent )
             :QAbstractItemDelegate( parent )
{ 
    m_selectedOverlay = QPixmap( ":buckets/avatar_overlay_selected.png" ); 
    m_overlay = QPixmap( ":buckets/avatar_overlay.png" ); 
}


void 
SeedDelegate::paint( QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index ) const
{
    painter->save();
    
    int flashValue = index.data( moose::HighlightRole ).isValid() ? index.data( moose::HighlightRole ).toInt() : 0;
    
    QRect overlayRect = option.rect;
    overlayRect.setHeight( m_overlay.height() );
    QRect iconRect = overlayRect.adjusted( 1, 1, -1, -3 ); //allow margin between avatar and overlay
    QRect textRect = option.rect.adjusted( 0, overlayRect.height(), 0, 0 );
    
    QIcon icon = index.data( Qt::DecorationRole ).value<QIcon>();
    
    painter->setRenderHint(QPainter::SmoothPixmapTransform);
    
    //FIXME: why isn't the icon painting at 64x64? - this works around it 
    //       for now but the avatar is slightly blurry.
    painter->drawPixmap( iconRect, icon.pixmap( iconRect.size()));
    
    if( option.state & QStyle::State_Selected )
    {
        painter->drawPixmap( overlayRect, m_selectedOverlay );
    }
    else
    {
        painter->drawPixmap( overlayRect, m_overlay );
    }
    
    if( flashValue > 0 )
        painter->fillRect( option.rect, QColor( 0x0, 0x78, 0xff, ( 0xff * ((qreal)flashValue / 100.0f) )));
    
    painter->setPen( Qt::white );
    QFont f = painter->font();
    f.setPointSize( f.pointSize() - 4 );
    painter->setFont( f );
    
    
    QFontMetrics fm( f);
    QString text = fm.elidedText( index.data().toString(), Qt::ElideRight, textRect.width());
    textRect = fm.boundingRect(textRect, Qt::AlignCenter, text );
    
    if( option.state & QStyle::State_Selected )
        painter->fillRect( textRect, QColor( 0x056e99 ) );
    
    painter->setRenderHint( QPainter::Antialiasing );
    painter->drawText( textRect, Qt::AlignCenter, text );
    
    painter->restore();
}


QSize 
SeedDelegate::sizeHint( const QStyleOptionViewItem& option, const QModelIndex& index ) const
{
    Q_UNUSED( index );
    return option.rect.size();
}