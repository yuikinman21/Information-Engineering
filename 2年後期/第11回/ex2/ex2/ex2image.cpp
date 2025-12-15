//
//  ex2image.cpp
//  ex2image
//
//  Created by 内海 ゆづ子 on 2014/05/27.
//  Copyright (c) 2014年 内海 ゆづ子. All rights reserved.
//

#include "ex2image.h"

ex2image::ex2image() : imgdata( 0 )
{
}

ex2image::ex2image( int w, int h, int c ) : imgdata( 0 )
{
    this->width = w;
    this->height = h;
    this->channels = c;

    imgdata = new unsigned char[ this->width*this->height*this->channels ];
}

ex2image::ex2image( const ex2image& m ) : imgdata( 0 )
{
    	int i, j, k;
    this->width = m.img_width();
	this->height = m.img_height();
	this->channels = m.img_channels();
    
	imgdata = new unsigned char[ this->width*this->height*this->channels ];
	for( j=0; j<this->height; j++ ){
		for( i=0; i<this->width; i++ ){
			for( k=0; k<this->channels; k++ ){
				(*this)( i, j, k ) = m( i, j, k );
			}
		}
	}

}

ex2image::~ex2image()
{
    if( imgdata != 0 ){
        delete [] imgdata;
        imgdata = 0 ;
    }
}

bool ex2image::resize( int w, int h, int c )
{
	if( imgdata != 0 ){
		delete [] imgdata;
		imgdata = 0;
		this->width = this->height = this->channels = 0;
	}
	
	imgdata= new unsigned char[ w*h*c ];
	this->width = w;
	this->height = h;
	this->channels = c;
	
	return true;
}


bool ex2image::copy( const ex2image & i ){
    if( this->img_width() != i.img_width() || this->img_height() != i.img_height()  || this->img_channels() != i.img_channels() ){
        std::cerr << "コピー先の画像サイズが異なります"<< std::endl;
        return false;
	}
    memcpy( imgdata, i.imgdata, sizeof( unsigned char )*this->width*this->height*this->channels );
	
	return true;
}

unsigned char& ex2image::operator()( int x, int y, int c )
{
	if( x < 0 || x >=this->img_width() || y < 0 || y >= this->img_height() || c < 0 || c >= this->img_channels() ) throw;
	
	return imgdata[ this->width*this->channels*y + this->channels*x + c ];
}

unsigned char ex2image::operator()( int x, int y, int c ) const
{
    if( x < 0 || x >=this->img_width() || y < 0 || y >= this->img_height() || c < 0 || c >= this->img_channels() ){
        std::cerr << "メモリの範囲外です" << std::endl;
        exit( -1 );
    }
return imgdata[ this->width*this->channels*y + this->channels*x + c ];
}

ex2image& ex2image::operator =( const ex2image& i)
{
	if( this != &i ){
		resize( i.img_width(), i.img_height(), i.img_channels() );
		copy( i );
	}
	
	return *this;
}

bool ex2image::load( const char* s )
{
    
    std::fstream is;
    int img_w, img_h, img_c, i, j, k, i_w, i_h, i_c, data, max;
    char c, c1, c2;

    //ファイルを開く
    //std::cout << s << std::endl;
    is.open( s, std::ios::in );
    if( !is.is_open() ){
        std::cerr << "cannot open the file!: " << s << std::endl;
        exit( -1 );
    }
    
    
    is.seekg( 0, std::ios::beg );

    is.get( c1 ).get( c2 ) >> std::ws;

    //読み込む画像の形式を調べる
//P2:グレースケールascii P3:フルカラーascii P5:グレースケールバイナリ　P6:フルカラーバイナリ
if( !( c1 == 'P' && ( c2 == '2' || c2 == '3' || c2 == '5' || c2 == '6' ) ) ){
    throw;
}
//グレースケール
else if( c2 == '2' || c2 == '5' ){
    img_c = 1;
    
}
//フルカラー
else if( c2 == '3' || c2 == '6' ){
    img_c = 3;
}

//コメントのスキップを行って，画像の幅と大きさを取得
skipcomments( is );
is >> img_w;
//マルチプロセスへの影響を考慮して，出力をやめる
//std::cout << img_w << std::endl;

skipcomments( is );
is >> img_h;
//マルチプロセスへの影響を考慮して，出力をやめる
//std::cout << img_h << std::endl;

skipcomments( is );

//最大値を読み出す．
if( c2 == '2' || c2 == '3' ){
    is >> max >> std::ws;
}
else{
    is >> max;
    is.get( c );
}



resize( img_w, img_h, img_c );

i_h = this->img_height();
i_w = this->img_width();
i_c = this->img_channels();


//ascii の場合
if( c2 == '2' || c2 == '3' ){
    for( j=0; j<i_h; j++ ){
        for( i=0; i<i_w; i++ ){
            for( k=0; k<i_c; k++ ){
                is >> data;
                ( *this )( i, j, k ) = ( unsigned char )data;
            }
        }
    }
}

else if( c2 == '5' || c2 == '6' ){
    
    for( j=0; j<i_h; j++ ){
        for( i=0; i<i_w; i++ ){
            for( k=0; k<i_c; k++ ){
                is.get( c );
                ( *this )( i, j, k ) = ( unsigned char )c;
            }
        }
    }
}

    is.close();
    return true;
}

void ex2image::skipcomments( std::istream& is )
{
    char c;
	
	while( true ){
		is.get( c );
		if( c == '#' ){
			while( c != '\n' ){
				is.get( c );
			}
		}
		
		else{
			is.putback( c );
			break;
		}
	}
	
}


bool ex2image::write( const char *s )
{
    std::fstream os;
    os.open( s, std::ios::out|std::ios::trunc );
    if( !os.is_open() ){
        std::cerr << "cannot open the file!: " << s << std::endl;
        exit( -1 );
    }
    
    int i, j, k, i_w = this->img_width(), i_h = this->img_height(), i_c = this->img_channels();
	
	if( imgdata == 0 ) throw;
	
	if( this->img_channels() == 1 ){
		os << "P2" << std::endl;
	}
	
	else if( this->img_channels() == 3 ){
		os << "P3" << std::endl;
	}
	
	os << this->img_width() << " " << this->img_height() << std::endl;
	
	os << 255 << std::endl;
	
	for( j=0; j<i_h; j++ ){
		for( i=0; i<i_w; i++ ){
			for( k=0; k<i_c; k++ ){
				os << (int)( *this )( i, j, k ) << " ";
			}
		}
		os << std::endl;
	}
	os << std::endl;
	
    os.close();
    
	return true;
}


