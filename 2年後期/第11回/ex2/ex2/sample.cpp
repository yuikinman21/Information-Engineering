//
//  sample.cpp
//  ex2image
//
//  Created by 内海 ゆづ子 on 2014/05/27.
//  Copyright (c) 2014年 内海 ゆづ子. All rights reserved.
//

#include <iostream>
#include "ex2image.h"

int main(int argc, const char * argv[])
{
    ex2image img;
    std::string s_file = "block.pgm";
    if( !img.load( s_file.c_str() ) ){
	  std::cerr << "cannot open the file!:" <<  s_file << std::endl;
	  exit( -1 );
	}

	//保存用の画像のバッファ
    ex2image inverse( img );

	//画像を反転させる
	int w = inverse.img_width();
	int h = inverse.img_height();
	for( int j=0; j<h; j++ ){
	  for( int i=0; i<w; i++ ){
		inverse( i, j, 0 ) = 255 - img( i , j, 0 );
	  }
	}
	
    if( !inverse.write( "inverse.pgm" ) ){
	  std::cerr << "cannot write the file!: inverse.pgm" << std::endl;
	  exit( -1 );
	} 
    
    return 0;
}

