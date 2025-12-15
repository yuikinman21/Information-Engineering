//
//  ex2image.h
//  ex2image
//
//  Created by 内海 ゆづ子 on 2014/05/27.
//  Copyright (c) 2014年 内海 ゆづ子. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cstdlib>


class ex2image
{
protected:
	int width, height, channels;
	unsigned char *imgdata;

public:
    
    //コンストラクタ
    ex2image();
	//コンストラクタ（画像サイズを指定）（w:幅，h:高さ，c:画素のチャンネル数）
	ex2image( int w, int h, int c );
	//コンストラクタ（初期化に他のオブジェクトを使う場合）
	ex2image( const ex2image& i );
	//デストラクタ
	~ex2image();
    
	//バッファのリサイズ
    bool resize( int w, int h, int c );
    //コピー
    bool copy( const ex2image & i );

    //画素値へのアクセス（x:x座標，y:y座標，c: チャンネル（グレースケールは0）
    unsigned char& operator()( int x, int y, int c );
    unsigned char operator()( int x, int y, int c ) const;
    
	//画像の幅にアクセス
	int img_width() const { return width; };
	//画像の高さにアクセス
	int img_height() const { return height; };
	//画像のチャンネル数にアクセス
	int img_channels() const { return channels; };
    
	//画像の代入
    ex2image& operator =( const ex2image& i);
	
	//画像の読み込み
	bool load( const char* s);
	//画像のコメントの読み飛ばし（皆さんは使う必要はありません）
	void skipcomments( std::istream& is );
	//画像の書き込み
	bool write( const char* s);
	
};



