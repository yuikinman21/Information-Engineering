import java.io.BufferedReader;
import java.io.FileReader;
import java.io.DataOutputStream;
import java.io.FileOutputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.Enumeration;
import java.util.Hashtable;
import java.util.Vector;
import java.lang.reflect.Method;
import java.lang.reflect.Modifier;

class Chavac{
  // ライブラリ関数(println()など)を提供するクラス名
  private static final String LIBRARY_NAME = "Chava";

  // トークンを表す定数群
  private static final int COMMA              = ',';
  private static final int SEMICOLON          = ';';
  private static final int L_BRACE            = '{';
  private static final int R_BRACE            = '}';
  private static final int L_PARENTHESIS      = '(';
  private static final int R_PARENTHESIS      = ')';
  private static final int DIVIDE             = '/';
  private static final int MINUS              = '-';
  private static final int MULTIPLY           = '*';
  private static final int PLUS               = '+';
  private static final int SUBSTITUTE         = '=';
  private static final int EXCLAMATION        = '!';
  private static final int CMP_Greater        = '>';
  private static final int CMP_Less           = '<';
  private static final int CMP_GreaterOrEqual = -1;
  private static final int CMP_LessOrEqual    = -2;
  private static final int CMP_Equal          = -3;
  private static final int CMP_NotEqual       = -4;
  private static final int EOF                = -5;
  private static final int TYPE_int           = -6;
  private static final int TYPE_void          = -7;
  private static final int TYPE_invalid       = -8;
  private static final int CONSTANT_int       = -9;
  private static final int IDENTIFIER         = -10;
  private static final int IF                 = -11;
  private static final int WHILE              = -12;
  private static final int RETURN             = -13;

  // Javaのバイトコードに対応する定数群
  private static final int BC_iconst_m1       = 0x02;
  private static final int BC_iconst_0        = 0x03;
  private static final int BC_iconst_1        = 0x04;
  private static final int BC_iconst_2        = 0x05;
  private static final int BC_iconst_3        = 0x06;
  private static final int BC_iconst_4        = 0x07;
  private static final int BC_iconst_5        = 0x08;
  private static final int BC_bipush          = 0x10;
  private static final int BC_sipush          = 0x11;
  private static final int BC_ldc             = 0x12;
  private static final int BC_ldc_w           = 0x13;
  private static final int BC_iload           = 0x15;
  private static final int BC_iload_0         = 0x1a;
  private static final int BC_iload_1         = 0x1b;
  private static final int BC_iload_2         = 0x1c;
  private static final int BC_iload_3         = 0x1d;
  private static final int BC_aload_0         = 0x2a;
  private static final int BC_istore          = 0x36;
  private static final int BC_istore_0        = 0x3b;
  private static final int BC_istore_1        = 0x3c;
  private static final int BC_istore_2        = 0x3d;
  private static final int BC_istore_3        = 0x3e;
  private static final int BC_pop             = 0x57;
  private static final int BC_iadd            = 0x60;
  private static final int BC_isub            = 0x64;
  private static final int BC_imul            = 0x68;
  private static final int BC_idiv            = 0x6c;
  private static final int BC_ineg            = 0x74;
  private static final int BC_if_icmpeq       = 0x9f;
  private static final int BC_if_icmpne       = 0xa0;
  private static final int BC_if_icmplt       = 0xa1;
  private static final int BC_if_icmpge       = 0xa2;
  private static final int BC_if_icmpgt       = 0xa3;
  private static final int BC_if_icmple       = 0xa4;
  private static final int BC_goto            = 0xa7;
  private static final int BC_ireturn         = 0xac;
  private static final int BC_return          = 0xb1;
  private static final int BC_getstatic       = 0xb2;
  private static final int BC_putstatic       = 0xb3;
  private static final int BC_invokespecial   = 0xb7;
  private static final int BC_invokestatic    = 0xb8;
  private static final int BC_wide            = 0xc4;
  private static final int BC_goto_w          = 0xc8;

  private TokenStream  _tokenstream;    // 字句解析系
  private Library      _library;        // ライブラリ
  private CodeBuffer   _code_buffer;    // コンパイル済みコードの一時格納先
  private String       _classfile_name; // 出力クラスファイル名

  private ConstantPool _constant_pool;  // 定数プール
  private int _this_class;       // 定数プールにおける出力クラス名の登録先スロット番号
  private int _super_class;      // 定数プールにおける親クラス名の登録先スロット番号
  private Fields       _fields;	 // 入力ソースコードが定義した大域変数を登録する辞書
  private Methods      _methods; // 入力ソースコードが定義した関数を登録する辞書

  // コンパイルエラー
  private class CompileError extends Error{
    private CompileError(String filename, int line_no, String message){
      super(filename + ":" + line_no + ": " + message);
    }

    CompileError(String message){
      this(_tokenstream.getFileName(), _tokenstream.getLineNo(), message);
    }

    CompileError(String message, Node node){
      this(node.getFileName(), node.getLineNo(), message);
    }
  }

  // 字句解析系：入力文字列をトークンの列に切り分ける
  private class TokenStream extends BufferedReader{
    private String _filename;	   // 入力ファイル名
    private String _line;	   // 読込中の行
    private int    _line_no;	   // 読込中の行番号
    private int    _max_index;	   // 読込中の行が含む文字数
    private int    _current_index; // 読込中の行における，次に読み込む文字の位置
    private int    _current_token; // 最後に読み込んだトークン
    private String _identifier;	   // 最後に読み込んだ識別子の値(文字列)
    private long   _int_value;	   // 最後に読み込んだ整数の値

    // コンストラクタ: 字句解析系の初期設定をおこなう
    TokenStream(String filename) throws IOException{
      super(new FileReader(filename));
      _filename = filename;
      _line_no  = 0;
      readNextLine();
    }

    // 次の行を読み込む処理: 空行は読み飛ばす
    private void readNextLine() throws IOException{
      while((_line = readLine()) != null){
	_line_no++;
	if ((_max_index = _line.length()) > 0){	// 空行でないなら
	  _current_index   = 0;	// 次に読み込む文字の位置を行先頭に移して
	  break;		// 読込み完了
	}
      }
    }

    private char nextChar(){ // 次に読み込む文字を返戻する処理
      if (_current_index < _max_index){
	return (_line.charAt(_current_index));
      }
      else{
	return (' ');
      }
    }

    int nextToken() throws IOException{ // 次のトークンを読み込んで返戻する処理
      char next_character;

      if (_line == null){ // 全ての行を読込み済みならEOFを返戻
	return (_current_token = EOF);
      }

      do{ // 空白文字を読み飛ばす
	if (_current_index == _max_index){
	  readNextLine();
	  if (_line == null){ // 全ての行を読込み済みならEOFを返戻
	    return (_current_token = EOF);
	  }
	}
	next_character = _line.charAt(_current_index++); // 次の文字を読み込む
      }while(Character.isWhitespace(next_character));

      switch(next_character){ // 次の文字に応じてトークンを切り出す
      case DIVIDE:                                       // '/'
	if (nextChar() == DIVIDE){ // '/'が2つ続いたらコメント
	  readNextLine();          // コメント部を読み飛ばして
	  return (nextToken());    // 読み飛ばしたコメントの次のトークンを返戻
	}

      case MINUS:                                        // '-'
      case MULTIPLY:                                     // '*'
      case PLUS:                                         // '+'
      case L_BRACE:                                      // '{'
      case R_BRACE:                                      // ']'
      case L_PARENTHESIS:                                // '('
      case R_PARENTHESIS:                                // ')'
      case SEMICOLON:                                    // ';'
      case COMMA:                                        // ','
	return (_current_token = (int)next_character);

      case SUBSTITUTE:
	if (nextChar() == '='){
	  _current_index++;
	  return (_current_token = CMP_Equal);           // '=='
	}
	else{
	    return (_current_token = SUBSTITUTE);        // '='
	}

      case EXCLAMATION:
	  if (nextChar() == '='){
	  _current_index++;
	  return (_current_token = CMP_NotEqual);       // '!='
	}
	else{
	  throw (new CompileError("Invalid Exclamation Mark"));
	}

      case CMP_Greater:
	if (nextChar() == '='){
	  _current_index++;
	  return (_current_token = CMP_GreaterOrEqual); // '>='
	}
	else{
	  return (_current_token = CMP_Greater);        // '>'
	}

      case CMP_Less:
	if (nextChar() == '='){
	_current_index++;
	return (_current_token = CMP_LessOrEqual);      // '<='
	}
	else{
	  return (_current_token = CMP_Less);           // '<'
	}

      default:
	if (Character.isLetter(next_character)){        // 英字(英字|数字)*
	  int begin_index = _current_index - 1;
	  while(Character.isLetterOrDigit(nextChar())){
	    _current_index++;
	  }
	  _identifier =
	    (_line.substring(begin_index, _current_index)).intern();
	  if (_identifier == "int"){                    // 予約語か確認
	    return (_current_token = TYPE_int);
	  }
	  else if (_identifier == "void"){
	    return (_current_token = TYPE_void);
	  }
	  else if (_identifier == "if"){
	    return (_current_token = IF);
	  }
	  else if (_identifier == "while"){
	    return (_current_token = WHILE);
	  }
	  else if (_identifier == "return"){
	    return (_current_token = RETURN);
	  }
	  else{
	    return (_current_token = IDENTIFIER); // 予約語でなければ識別子
	  }
	}
	else if (Character.isDigit(next_character)){    // 数字+
	  for(_int_value = (long)(Character.digit(next_character, 10));
	      Character.isDigit(next_character = nextChar());
	      _current_index++){
	    _int_value =
	      _int_value * 10 + (long)(Character.digit(next_character, 10));
	    if (_int_value > 0x80000000L){
	      throw (new CompileError("Integer Overflow"));
	    }
	  }
	  return (_current_token = CONSTANT_int);
	}
	else{
	  throw (new CompileError("Invalid Character")); // どれでもないのでエラー
	}
      }
    }

    int currentToken(){     // 最後に読み込んだトークンを返戻する
      return (_current_token);
    }

    String getFileName(){   // 入力ファイル名を返戻する
      return (_filename);
    }

    String getIdentifier(){ // 最後に読み込んだ識別子の値を返戻する
      return (_identifier);
    }

    int getIntValue(){      // 最後に読み込んだ整数の値を返戻する
      return ((int)(_int_value));
    }

    int getLineNo(){        // 読み込み中の行番号を返戻する
      return (_line_no);
    }
  }

  // 中間語の定義(構文解析，意味解析，コード生成)．中間表現は木構造をなす．
  private class Node{     // 全中間語の親クラス
    private Node _parent; // 親ノード．たとえばa+bの中間表現で，+はaおよびbの親
    int _line_no;         // ノード(this)に対応するソースコードの行番号

    Node(Node parent){    // コンストラクタ．メンバ変数_parentと_line_noを設定
      setParent(parent);
      _line_no = _tokenstream.getLineNo();
    }

    final void setParent(Node parent){
      _parent = parent;
    }

    String getFileName(){    // ノードに対応するソースコードのファイル名を取得
      return (_parent.getFileName()); // defaultの実装: 知らないことは親に聞く
    }

    int getLineNo(){
      return (_line_no);
    }

    int localVariableCount(){ // ノードが属するScopeで有効な局所変数の数を取得
      return (_parent.localVariableCount());
    }

    int getMethodReturnType(){ // ノードが属するメソッドの返戻値型を取得
      return (_parent.getMethodReturnType());
    }

    Expression parseReferenceOrCall(Node parent,
				    String name) throws IOException{
      // 識別子から先の構文解析: 局所 or 大域変数，あるいは関数呼出し
      return (_parent.parseReferenceOrCall(parent, name));
    }

    final Statement parseStatement(int token) throws IOException{
      // 文の構文解析: 次のトークンから，どの文か判定し，対応するコンストラクタを呼ぶ
      switch(token){
      case L_BRACE:                    // '{' だったらブロック文
	return (new BlockStatement(this));
      case IDENTIFIER:                 // 識別子だったら関数呼出しか代入文
      {
	Expression first_term =
	  parseReferenceOrCall(this, _tokenstream.getIdentifier());

	return (first_term.parseSuccessorStatement(this));
      }
      case IF:                         // ifだったらif文
	return (new IfStatement(this));
      case WHILE:                      // whileだったらwhile文
	return (new WhileStatement(this));
      case RETURN:                     // returnだったらreturn文
	return (new ReturnStatement(this));
      default:                         // どれでもなければエラー
	throw (new CompileError("Invalid Statement"));
      }
    }

    final Statement parseStatement() throws IOException{ // 文の構文解析
      return (parseStatement(_tokenstream.nextToken()));
    }

    /* 式の構文解析
     *
     * 式の構文解析については構文解析の章を参照されたい．
     *
     * 引数null_is_candidateは，式がなくても(null)よい場所の構文解析か
     * 否かを示す．たとえば関数呼出しの'func('まで読んで，その次には
     * 引数にあたる式がきてもいいし，何もなくても('func()')よい．
     */
    final Expression parseExpression(boolean null_is_candidate) throws IOException{
      Expression result = parseTerm(null_is_candidate);
      int token;

      if (result != null){
	while(((token = _tokenstream.currentToken()) == PLUS) ||
	      (token == MINUS)){
	  result = new BinaryOperator(this, token, result, parseTerm(false));
	}
      }

      return (result);
    }

    final Expression parseTerm(boolean null_is_candidate) throws IOException{
      Expression result = parseFactor(null_is_candidate);
      int token;

      if (result != null){
	while(((token = _tokenstream.nextToken()) == MULTIPLY) ||
	      (token == DIVIDE)){
	  result = new BinaryOperator(this, token, result, parseFactor(false));
	}
      }

      return (result);
    }

    final Expression parseFactor(boolean null_is_candidate) throws IOException{
      int token = _tokenstream.nextToken();
      Expression result;

      switch(token){
      case IDENTIFIER:
	result = parseReferenceOrCall(this, _tokenstream.getIdentifier());
	break;

      case MINUS:
      case PLUS:
	result = new UnaryOperator(this, token);
	break;

      case CONSTANT_int:
	result = new ConstantInt(this, _tokenstream.getIntValue());
	break;

      case L_PARENTHESIS:
	result = parseExpression(false);
	if (_tokenstream.currentToken() != R_PARENTHESIS){
	  throw (new CompileError("Invalid parenthesis"));
	}
	break;

      default:
	if (null_is_candidate){
	  result = null;
	}
	else{
	  throw (new CompileError("Invalid factor"));
	}
      }

      return (result);
    }
  }

  private abstract class Expression extends Node{ // 式を表す全中間語の親クラス

    Expression(Node parent){
      super(parent);
    }

    Statement parseSuccessorStatement(Node parent) throws IOException{
      throw (new CompileError("Shoud Not Reach Here"));
    }

    // 式の計算結果を与える目的コードをbufferに出力する．
    abstract int emitRCode(CodeBuffer buffer, int sp) throws IOException;
  }

  private abstract class Variable extends Expression{ // 変数を表す中間語
    int     _type_id;  // 変数の型

    Variable(Node parent, int type_id){
      super(parent);
      _type_id  = type_id;
    }

    // 自身と同じ変数を参照するノードを生成する．
    abstract Variable createReference(Node parent);

    // 最初が変数参照である文(つまり代入文)の続きを構文解析する
    Statement parseSuccessorStatement(Node parent) throws IOException{
      return (new SubstituteStatement(parent, this));
    }

    abstract void emitCode(CodeBuffer buffer,
			   boolean is_load) throws IOException;

    // 変数に値を代入する際のコードを出力する
    int emitLCode(CodeBuffer buffer) throws IOException{
      emitCode(buffer, false);
      return (_type_id);
    }

    int emitRCode(CodeBuffer buffer, int sp) throws IOException{
      switch(_type_id){
      case TYPE_int:
	buffer.setMaxStack(sp+1);
	break;
      default:
	throw (new CompileError("Not Supported Type", this));
      }

      emitCode(buffer, true);
      return (_type_id);
    }
  }

  private class GlobalVariable extends Variable{ // 大域変数を表す中間語
    private int _reference_index; // 定数プールにおける大域変数名の登録先スロット番号

    GlobalVariable(Node parent, int type_id, int reference_index){
      super(parent, type_id);
      _reference_index = reference_index;
    }

    Variable createReference(Node parent){
      return (new GlobalVariable(parent, _type_id, _reference_index));
    }

    void emitCode(CodeBuffer buffer,
		  boolean is_load) throws IOException{
      buffer.writeUnsignedByte(is_load ? BC_getstatic : BC_putstatic);
      buffer.writeUnsignedShort(_reference_index);
    }
  }

  private class LocalVariable extends Variable{ // 局所変数を表す中間語
    private int _index; // スタックフレームにおける局所変数の格納先スロット番号

    LocalVariable(Node parent, int type_id, int index){
      super(parent, type_id);
      _index    = index;
    }

    Variable createReference(Node parent){
      return (new LocalVariable(parent, _type_id, _index));
    }

    void emitCode(CodeBuffer buffer,
    			  boolean is_load) throws IOException{
      int code_offset = is_load ? 0 : (BC_istore - BC_iload);
      int short_opcode_base;
      int long_opcode;

      switch(_type_id){
      case TYPE_int:
	short_opcode_base = BC_iload_0 + code_offset;
	long_opcode       = BC_iload + code_offset;
	break;
      default:
	throw (new CompileError("Not Supported Type", this));
      }
      if (_index <= 3){
	buffer.writeUnsignedByte(short_opcode_base + _index);
      }
      else if (_index <= 255){
	buffer.writeUnsignedByte(long_opcode);
	buffer.writeUnsignedByte(_index);
      }
      else{
	buffer.writeUnsignedByte(BC_wide);
	buffer.writeUnsignedByte(long_opcode);
	buffer.writeUnsignedShort(_index);
      }
    }
  }

  private class ConstantInt extends Expression{ // 整定数を表す中間語
    private int _value; // 整定数の値
    private int _index; // 定数プールにおける整定数の登録先スロット番号

    ConstantInt(Node parent, int value){
      super(parent);
      _value = value;
      if ((value > Short.MAX_VALUE) || (value < Short.MIN_VALUE)){
	_index = _constant_pool.putInteger(value);
      }
    }

    int emitRCode(CodeBuffer buffer, int sp) throws IOException{
      buffer.setMaxStack(sp+1);

      if ((-1 <= _value) && (_value <= 5)){
	buffer.writeUnsignedByte(BC_iconst_0 + _value);
      }
      else if ((Byte.MIN_VALUE <= _value) && (_value <= Byte.MAX_VALUE)){
	buffer.writeUnsignedByte(BC_bipush);
	buffer.writeByte(_value);
      }
      else if ((Short.MIN_VALUE <= _value) && (_value <= Short.MAX_VALUE)){
	buffer.writeUnsignedByte(BC_sipush);
	buffer.writeShort(_value);
      }
      else if (_index < 256){
	buffer.writeUnsignedByte(BC_ldc);
	buffer.writeUnsignedByte(_index);
      }
      else{
	buffer.writeUnsignedByte(BC_ldc_w);
	buffer.writeUnsignedShort(_index);
      }
      return (TYPE_int);
    }
  }

  private class UnaryOperator extends Expression{ // 単項演算子を表す中間語
    private int _operator;          // 単項演算子の種別: + or -
    private Expression _expression; // 単項演算子に続く式

    UnaryOperator(Node parent,
		  int operator) throws IOException{
      super(parent);
      _operator   = operator;
      _expression = parseFactor(false);
    }

    int emitRCode(CodeBuffer buffer, int sp) throws IOException{
      int type_id = _expression.emitRCode(buffer, sp);
      int op_code;

      switch(type_id){
      case TYPE_int:
	op_code = BC_ineg;
	break;
      default:
	throw (new CompileError("Type Mismatch", this));
      }
      if (_operator == MINUS){
	buffer.writeUnsignedByte(op_code);
      }
      return (type_id);
    }
  }

  private class BinaryOperator extends Expression{ // 二項演算子を表す中間語
    private int _operator;                // ニ項演算子の種別: +, -, *, /
    private Expression _left_expression;  // ニ項演算子の左側の式
    private Expression _right_expression; // ニ項演算子の右側の式

    BinaryOperator(Node parent,
		   int operator,
		   Expression left_expression,
		   Expression right_expression) throws IOException{
      super(parent);
      _operator = operator;
      _left_expression = left_expression;
      _left_expression.setParent(this);
      _right_expression = right_expression;
      _right_expression.setParent(this);
    }

    int emitRCode(CodeBuffer buffer, int sp) throws IOException{
      int op_code;
      int type_id;

      switch(_operator){
      case DIVIDE:
	op_code = BC_idiv;
	break;
      case MINUS:
	op_code = BC_isub;
	break;
      case MULTIPLY:
	op_code = BC_imul;
	break;
      case PLUS:
	op_code = BC_iadd;
	break;
      default:
	throw (new CompileError("Unsupported Operator", this));
      }

      if ((type_id = _left_expression.emitRCode(buffer, sp)) ==
	  (_right_expression.emitRCode(buffer, sp+1))){
	switch(type_id){
	case TYPE_int:
	  buffer.writeUnsignedByte(op_code);
	  return (type_id);
	default:
	}
      }
      throw (new CompileError("Type Mismatch", this));
    }
  }

  private class CallExpression extends Expression{ // 関数呼出しを表す中間語
    private String _name;         // 関数名
    private Vector _arguments;    // 実引数
    private String _identifier;   // 関数名 + 引数および返戻値型
    private int _return_type;     // 返戻値型
    private int _reference_index; // 定数プールにおける呼出先メソッドの登録スロット番号

    CallExpression(Node parent,
		   String name) throws IOException{
      super(parent);
      _name = name;                   // 構文解析: 関数呼出しとは識別子nameに
      _arguments = new Vector();

      if (_tokenstream.nextToken() == L_PARENTHESIS){ // '('が続き
	Expression argument = parseExpression(true);  // 任意個の実引数が続き

	if (argument != null){
	  _arguments.addElement(argument);
	  while(_tokenstream.currentToken() == COMMA){
	    _arguments.addElement(parseExpression(false));
	  }
	}

	if (_tokenstream.currentToken() == R_PARENTHESIS){ // 最後に')'がくるものである
	  _identifier = null;          // 返戻値型は，まだ判らないから放置
	  _return_type = TYPE_invalid;
	  _reference_index = 0;
	  return;                      // 正常に構文解析が終了したので戻る
	}
      }

      throw (new CompileError("Parse Error in Call")); // さもなくばエラー
    }

    // 手続呼出しの構文解析
    Statement parseSuccessorStatement(Node parent) throws IOException{
      return (new CallStatement(parent, this));
    }

    final String getIdentifier(){
      return (_identifier);
    }

    final void patch(int return_type, int reference_index){
      _return_type = return_type;         // 返戻値型と定数プールにおける呼出先
      _reference_index = reference_index; // メソッドの登録スロット番号の設定
    }

    int emitRCode(CodeBuffer buffer, int sp) throws IOException{
      // identifierの決定
      StringBuffer identifier_buffer = new StringBuffer(_name);

      identifier_buffer.append("(");
      for(int i=0; i<_arguments.size(); i++){
	Expression argument = (Expression)(_arguments.elementAt(i));

	switch(argument.emitRCode(buffer, sp+i)){
	case TYPE_int:
	  identifier_buffer.append("I");
	  break;
	default:
	  throw (new CompileError("Unsupported Argument Type", this));
	}
      }
      identifier_buffer.append(")");
      _identifier = identifier_buffer.toString();

      // identifierに一致する呼出先を検索し_return_typeと_reference_indexを特定
      if (!(_methods.resolve(this) || _library.resolve(this))){
	throw (new CompileError("Function Not Found", this));
      }

      // コードの出力
      switch(_return_type){
      case TYPE_int:
	buffer.setMaxStack(sp+1);
      default:
      }
      buffer.writeUnsignedByte(BC_invokestatic);
      buffer.writeUnsignedShort(_reference_index);

      return (_return_type);
    }
  }

  private abstract class Statement extends Node{ // 文を表す全中間語の親クラス
    Statement(Node parent){
      super(parent);
    }

    abstract boolean emitCode(CodeBuffer buffer) throws IOException;
  }

  private class SubstituteStatement extends Statement{ // 代入文を表す中間語
    private Variable   _destination;
    private Expression _source;

    SubstituteStatement(Node parent,
			Variable destination) throws IOException{
      super(parent);
      _destination = destination;     // 構文解析: 代入文とは変数destinationに
      _destination.setParent(this);
      if (_tokenstream.nextToken() == SUBSTITUTE){      // '=' が続き
	_source = parseExpression(false);               // 更に式がきて
	if (_tokenstream.currentToken() == SEMICOLON){  // 最後に';'がくるものである
	  return;                     // 正常に構文解析が終了したので戻る
	}
      }
      throw (new CompileError("Invalid Substitution")); // さもなくばエラー
    }

    boolean emitCode(CodeBuffer buffer) throws IOException{ // コード生成
      if (_source.emitRCode(buffer, 0) != _destination.emitLCode(buffer)){
	throw (new CompileError("Type Mismatch", this));
      }
      return (false);
    }
  }

  private class CallStatement extends Statement{ // 手続呼出文を表す中間語
    private CallExpression _call_expression;

    CallStatement(Node parent,
		  CallExpression call_expression) throws IOException{
      super(parent);           // 構文解析: 手続呼出文とは．関数呼出しで始まり
      _call_expression = call_expression; 
      _call_expression.setParent(this);
      if (_tokenstream.nextToken() == SEMICOLON){ // つぎに';'がくるものである
	return;                // 正常に構文解析が終了したので戻る
      }
      throw (new CompileError("Invalid Call")); // さもなくばエラー
    }

    boolean emitCode(CodeBuffer buffer) throws IOException{ // コード生成
      switch(_call_expression.emitRCode(buffer, 0)){
      case TYPE_int:
	buffer.writeUnsignedByte(BC_pop);
      }
      return (false);
    }
  }

  private abstract class ConditionStatement extends Statement{ // 分岐を含む文の親クラス
    int _condition;           // 比較演算子
    Expression _l_expression; // 比較演算子の左側の式
    Expression _r_expression; // 比較演算子の右側の式
    Statement  _statement;    // 条件成立時に実行する文

    ConditionStatement(Node parent) throws IOException{
      super(parent); // 構文解析: 分岐を含む文とは，最初にifまたはwhileがきて
      if (_tokenstream.nextToken() == L_PARENTHESIS){       // '('が続き
	_l_expression = parseExpression(false);             // 式が続き
	switch(_condition = _tokenstream.currentToken()){   // 比較演算子が続き
	case CMP_Equal:
	case CMP_NotEqual:
	case CMP_Greater:
	case CMP_GreaterOrEqual:
	case CMP_Less:
	case CMP_LessOrEqual:
	  _r_expression = parseExpression(false);            // 式が続き
	  if (_tokenstream.currentToken() == R_PARENTHESIS){ // ';'が続き
	    _statement = parseStatement();    // 最後に文がくるものである
	    return;                           // 正常に終了したので戻る
	  }
	default:
	  break;
	}
      }
      throw (new CompileError("Condition Parse Error")); // さもなくばエラー
    }
  }

  private class IfStatement extends ConditionStatement{ // if文を表す中間語
    IfStatement(Node parent) throws IOException{
      super(parent);
    }

    boolean emitCode(CodeBuffer buffer) throws IOException{ // コード生成
      int pc, offset;
      _l_expression.emitRCode(buffer, 0);
      _r_expression.emitRCode(buffer, 1);
      pc = buffer.commit(3);
      _statement.emitCode(buffer);
      offset = buffer.pc() - pc;
      if (offset <= Short.MAX_VALUE){
	switch(_condition){
	case CMP_Equal:
	  buffer.patchUnsignedByte(pc, BC_if_icmpne);
	  break;
	case CMP_NotEqual:
	  buffer.patchUnsignedByte(pc, BC_if_icmpeq);
	  break;
	case CMP_Greater:
	  buffer.patchUnsignedByte(pc, BC_if_icmple);
	  break;
	case CMP_GreaterOrEqual:
	  buffer.patchUnsignedByte(pc, BC_if_icmplt);
	  break;
	case CMP_Less:
	  buffer.patchUnsignedByte(pc, BC_if_icmpge);
	  break;
	case CMP_LessOrEqual:
	  buffer.patchUnsignedByte(pc, BC_if_icmpgt);
	  break;
	default:
	  throw (new CompileError("Internal Error: Invalid Condition", this));
	}
	buffer.patchShort(pc+1, offset);
      }
      else{
	buffer.insert(pc, 5);
	offset = offset + 5 - 3;
	switch(_condition){
	case CMP_Equal:
	  buffer.patchUnsignedByte(pc, BC_if_icmpeq);
	  break;
	case CMP_NotEqual:
	  buffer.patchUnsignedByte(pc, BC_if_icmpne);
	  break;
	case CMP_Greater:
	  buffer.patchUnsignedByte(pc, BC_if_icmpgt);
	  break;
	case CMP_GreaterOrEqual:
	  buffer.patchUnsignedByte(pc, BC_if_icmpge);
	  break;
	case CMP_Less:
	  buffer.patchUnsignedByte(pc, BC_if_icmplt);
	  break;
	case CMP_LessOrEqual:
	  buffer.patchUnsignedByte(pc, BC_if_icmple);
	  break;
	default:
	  throw (new CompileError("Internal Error: Invalid Condition", this));
	}
	buffer.patchShort(pc+1, 8);
	buffer.patchUnsignedByte(pc+3, BC_goto_w);
	buffer.patchInt(pc+4, offset);
      }
      return (false);
    }
  }

  private class WhileStatement extends ConditionStatement{ // while文を表す中間語
    WhileStatement(Node parent) throws IOException{
      super(parent);
    }

    boolean emitCode(CodeBuffer buffer) throws IOException{ // コード生成
      int pc, offset;
      pc = buffer.commit(3);
      _statement.emitCode(buffer);
      offset = buffer.pc() - pc;
      if (offset <= Short.MAX_VALUE){
	buffer.patchUnsignedByte(pc, BC_goto);
	buffer.patchShort(pc+1, offset);
	pc = pc + 3;
      }
      else{
	buffer.insert(pc, 2);
	buffer.patchUnsignedByte(pc, BC_goto_w);
	buffer.patchInt(pc+1, offset);
	pc = pc + 5;
      }
      _l_expression.emitRCode(buffer, 0);
      _r_expression.emitRCode(buffer, 1);
      offset = pc - buffer.pc();
      if (offset >= Short.MIN_VALUE){
	switch(_condition){
	case CMP_Equal:
	  buffer.writeUnsignedByte(BC_if_icmpeq);
	  break;
	case CMP_NotEqual:
	  buffer.writeUnsignedByte(BC_if_icmpne);
	  break;
	case CMP_Greater:
	  buffer.writeUnsignedByte(BC_if_icmpgt);
	  break;
	case CMP_GreaterOrEqual:
	  buffer.writeUnsignedByte(BC_if_icmpge);
	  break;
	case CMP_Less:
	  buffer.writeUnsignedByte(BC_if_icmplt);
	  break;
	case CMP_LessOrEqual:
	  buffer.writeUnsignedByte(BC_if_icmple);
	  break;
	default:
	  throw (new CompileError("Internal Error: Invalid Condition", this));
	}
	buffer.writeShort(offset);
      }
      else{
	switch(_condition){
	case CMP_Equal:
	  buffer.writeUnsignedByte(BC_if_icmpne);
	  break;
	case CMP_NotEqual:
	  buffer.writeUnsignedByte(BC_if_icmpeq);
	  break;
	case CMP_Greater:
	  buffer.writeUnsignedByte(BC_if_icmple);
	  break;
	case CMP_GreaterOrEqual:
	  buffer.writeUnsignedByte(BC_if_icmplt);
	  break;
	case CMP_Less:
	  buffer.writeUnsignedByte(BC_if_icmpge);
	  break;
	case CMP_LessOrEqual:
	  buffer.writeUnsignedByte(BC_if_icmpgt);
	  break;
	default:
	  throw (new CompileError("Internal Error: Invalid Condition", this));
	}
	buffer.writeShort(8);
	buffer.writeUnsignedByte(BC_goto_w);
	buffer.writeInt(offset-3);
      }
      return (false);
    }
  }

  private class ReturnStatement extends Statement{ // return文を表す中間語
    private Expression _return_value;              // 返戻値にあたる式

    ReturnStatement(Node parent) throws IOException{
      super(parent);
      {
	int token;                          // 構文解析: メソッドの返戻値型が

	if (getMethodReturnType() == TYPE_void){ // voidなら返戻値なし
	  _return_value = null;
	  token = _tokenstream.nextToken();
	}
	else{                                     // そうでないなら
	  _return_value = parseExpression(false); // returnに続いて式がきて
	  token = _tokenstream.currentToken();
	}

	if (token != SEMICOLON){                  // 最後に';'がくるはず
	  throw (new CompileError("Invalid Return")); // こないならエラー
	}
      }
    }

    boolean emitCode(CodeBuffer buffer) throws IOException{ // コード生成
      switch(getMethodReturnType()){
      case TYPE_void:
	buffer.writeUnsignedByte(BC_return);
	break;
      case TYPE_int:
	if (_return_value.emitRCode(buffer, 0) == TYPE_int){
	  buffer.writeUnsignedByte(BC_ireturn);
	  break;
	}
      default:
	throw (new CompileError("Invalid Return Type", this));
      }
      return (true);
    }
  }

  private class BlockStatement extends Statement{ // ブロック文を表す中間語
    private Block _block;

    BlockStatement(Node parent) throws IOException{
      super(parent);
      _block = new Block(this);
    }

    boolean emitCode(CodeBuffer buffer) throws IOException{ // コード生成
      return (_block.emitCode(buffer));
    }
  }

  // スコープ(局所変数の有効範囲，つまり中括弧の内部)を表す中間語
  private abstract class Scope extends Node{
    Hashtable _local_variable_table; // 意味解析用の局所変数表
    int       _local_variable_count; // 局所変数の新規登録時に符番する番号

    Scope(Node parent){
      super(parent);
      _local_variable_table = new Hashtable();
      _local_variable_count =
	(parent == null) ? 0 : parent.localVariableCount();
    }

    void putLocalVariable(int type_id, String name){ // 局所変数の登録
      if (!(_local_variable_table.containsKey(name))){
	Variable declared_variable =
	  new LocalVariable(this, type_id, _local_variable_count++);
	_local_variable_table.put(name, declared_variable);
      }
      else{
	throw (new CompileError("Variable declared twice."));
      }
    }

    Variable createReference(Node parent, String name){
      // 名前がnameの局所変数が登録されていたら，該変数への参照を生成
      Variable variable = (Variable)(_local_variable_table.get(name));

      return ((variable == null) ? null : (variable.createReference(parent)));
    }

    int localVariableCount(){
      return (_local_variable_count);
    }
  }

  private class Block extends Scope{ // ブロックを表す中間語
    private Vector _statements;      // ブロック内にある文の中間表現の格納先

    Block(Node parent) throws IOException{
      super(parent);
      {
	int token;

	_statements = new Vector();         // 構文解析: ブロックとは'{'に続く
	while((token = _tokenstream.nextToken()) != R_BRACE){ // '}'がくるまで
	  switch(token){
	  case TYPE_int:
	    parseVariableDeclaration(token);               // 変数の宣言か
	    break;
	  default:
	    _statements.addElement(parseStatement(token)); // 文がくるものである
	  }
	}
      }
    }

    private void parseVariableDeclaration(int type_id) throws IOException{
      if (_tokenstream.nextToken() == IDENTIFIER){  // 構文解析: 変数宣言とは
	String name = _tokenstream.getIdentifier(); // 型，変数名に続いて
	if (_tokenstream.nextToken() == SEMICOLON){ // ';'がくるものである
	  putLocalVariable(type_id, name);          // 変数をBlock(Scope)に登録
	  return;                                   // 正常終了したので戻る
	}
      }
      throw (new CompileError("Invalid Declaration")); // さもなくばエラー
    }

    Expression parseReferenceOrCall(Node parent,    // 識別子から先の構文解析
				    String name) throws IOException{
      Expression result = createReference(parent, name); // 識別子は局所変数？

      if (result == null){                                 // そうでないなら
	result = super.parseReferenceOrCall(parent, name); // 親に判断を委ねる
      }

      return (result);
    }

    boolean emitCode(CodeBuffer buffer) throws IOException{ // コード生成
      Enumeration statements = _statements.elements();

      buffer.setMaxLocals(localVariableCount());
      while(statements.hasMoreElements()){   // 式に対応するコードを順次出力
	if (((Statement)(statements.nextElement())).emitCode(buffer)){
	  if (statements.hasMoreElements()){
	    throw (new CompileError("No statement can follow return",
				    (Statement)(statements.nextElement())));
	  }
	  else{
	    return (true);
	  }
	}
      }
      return (false);
    }
  }

  // 定数プール: 出力先クラスファイルに収める定数群(シンボルなど)の格納場所
  private final class ConstantPool extends Vector{
    // 定数プールに登録済みの要素を検索する際に使うハッシュ表群
    private Hashtable _class_table;		// クラス向け
    private Hashtable _name_and_type_table;	// 名前と型の組向け
    private Hashtable _integer_table;		// 整定数向け
    private Hashtable _methodref_table;		// メソッド向け
    private Hashtable _fieldref_table;		// フィールド向け
    private Hashtable _utf8_table;		// 文字列向け

    private abstract class Constant{ // 定数プールに登録するエントリの親クラス
      private int _index;

      void setIndex(int index){
	_index = index;
      }

      int getIndex(){
	return (_index);
      }

      // コード生成: クラスファイルの定数プールのエントリ1つ分の出力
      abstract void emitCode(DataOutputStream classfile) throws IOException;
    }

    private class ConstantClass extends Constant{ // クラスのエントリ
      private int _name_index;

      ConstantClass(int name_index){
	_name_index = name_index;
      }

      void emitCode(DataOutputStream classfile) throws IOException{
	classfile.writeByte(7); // CONSTANT_Class
	classfile.writeShort(_name_index);
      }
    }

    private class ConstantNameAndType extends Constant{ // 名前と型の組のエントリ
      private int _name_index;
      private int _descriptor_index;

      ConstantNameAndType(int name_index, int descriptor_index){
	_name_index = name_index;
	_descriptor_index = descriptor_index;
      }

      void emitCode(DataOutputStream classfile) throws IOException{
	classfile.writeByte(12); // CONSTANT_Class
	classfile.writeShort(_name_index);
	classfile.writeShort(_descriptor_index);
      }
    }

    private class ConstantInteger extends Constant{ // 整定数のエントリ
      private int _bytes;

      ConstantInteger(int bytes){
	_bytes = bytes;
      }

      void emitCode(DataOutputStream classfile) throws IOException{
	classfile.writeByte(3); // CONSTANT_Integer
	classfile.writeInt(_bytes);
      }
    }

    private class ConstantMethodref extends Constant{ // メソッドのエントリ
      private int _class_index;
      private int _name_and_type_index;

      ConstantMethodref(int class_index, int name_and_type_index){
	_class_index = class_index;
	_name_and_type_index = name_and_type_index;
      }

      void emitCode(DataOutputStream classfile) throws IOException{
	classfile.writeByte(10); // CONSTANT_Methodref
	classfile.writeShort(_class_index);
	classfile.writeShort(_name_and_type_index);
      }
    }

    private class ConstantFieldref extends Constant{ // フィールドのエントリ
      private int _class_index;
      private int _name_and_type_index;

      ConstantFieldref(int class_index, int name_and_type_index){
	_class_index = class_index;
	_name_and_type_index = name_and_type_index;
      }

      void emitCode(DataOutputStream classfile) throws IOException{
	classfile.writeByte(9); // CONSTANT_Fieldref
	classfile.writeShort(_class_index);
	classfile.writeShort(_name_and_type_index);
      }
    }

    private class ConstantUtf8 extends Constant{ // 文字列のエントリ
      private String _bytes;

      ConstantUtf8(String bytes){
	_bytes = bytes;
      }

      void emitCode(DataOutputStream classfile) throws IOException{
	classfile.writeByte(1); // CONSTANT_Fieldref
	classfile.writeUTF(_bytes);
      }
    }

    ConstantPool(){ // コンストラクタ: 検索用ハッシュ表群の生成
      _class_table         = new Hashtable();
      _name_and_type_table = new Hashtable();
      _integer_table       = new Hashtable();
      _methodref_table     = new Hashtable();
      _fieldref_table      = new Hashtable();
      _utf8_table          = new Hashtable();
    }

    private int put(Hashtable table, Object key, Constant element){ // エントリの登録
      int result;

      table.put(key, element);
      addElement(element);
      element.setIndex(result = size());

      return (result);
    }

    private Integer createKey(int index){ // ハッシュ表への登録に使う鍵の生成
      return (new Integer(index));
    }

    private Integer createKey(int index0, int index1){
      return (createKey((index0 << 16) | (index1 & 0xFFFF)));
    }

    private int putClass(int name_index){
      Integer key = createKey(name_index);
      Constant entry = (Constant)(_class_table.get(key));

      if (entry == null){
	return (put(_class_table, key, new ConstantClass(name_index)));
      }
      else{
	return (entry.getIndex());
      }
    }

    int putClass(String name){ // クラスの登録
      return putClass(putUtf8(name));
    }

    private int putNameAndType(int name_index, int descriptor_index){
      Integer key = createKey(name_index, descriptor_index);
      Constant entry = (Constant)(_name_and_type_table.get(key));

      if (entry == null){
	entry = new ConstantNameAndType(name_index, descriptor_index);
	return (put(_name_and_type_table, key, entry));
      }
      else{
	return (entry.getIndex());
      }
    }

    int putInteger(int value){ // 整定数の登録
      Integer key = createKey(value);
      Constant entry = (Constant)(_integer_table.get(key));

      if (entry == null){
	return (put(_integer_table, key, new ConstantInteger(value)));
      }
      else{
	return (entry.getIndex());
      }
    }

    int putMethodref(int class_index,
		     int name_index, int descriptor_index){ // メソッドの登録
      int name_and_type_index =
	putNameAndType(name_index, descriptor_index);
      Integer key = createKey(class_index, name_and_type_index);
      Constant entry = (Constant)(_methodref_table.get(key));

      if (entry == null){
	entry = new ConstantMethodref(class_index, name_and_type_index);
	return (put(_methodref_table, key, entry));
      }
      else{
	return (entry.getIndex());
      }
    }

    int putMethodref(int methodname_index, int descriptor_index){
      return (putMethodref(_this_class,
			   methodname_index, descriptor_index));
    }

    int putFieldref(int name_index, int descriptor_index){ // フィールドの登録
      int class_index = _this_class;
      int name_and_type_index = putNameAndType(name_index, descriptor_index);
      Integer key = createKey(class_index, name_and_type_index);
      Constant entry = (Constant)(_fieldref_table.get(key));

      if (entry == null){
	entry = new ConstantFieldref(class_index, name_and_type_index);
	return (put(_fieldref_table, key, entry));
      }
      else{
	return (entry.getIndex());
      }
    }

    int putUtf8(String utf8){ // 文字列の登録
      Constant entry = (Constant)(_utf8_table.get(utf8));

      if (entry == null){
	return (put(_utf8_table, utf8, new ConstantUtf8(utf8)));
      }
      else{
	return (entry.getIndex());
      }
    }

    // コード生成: クラスファイルの定数プール部分を生成する
    void emitCode(DataOutputStream classfile) throws IOException{
      int size = size();

      if (size >= 65534){
	throw (new IOException("Too Big Classfile"));
      }
      classfile.writeShort(size + 1);
      for(int i=0; i<size; i++){
	((Constant)elementAt(i)).emitCode(classfile);
      }
    }
  }

  private final class Fields extends Hashtable{ // 大域変数群を格納する辞書
    private class Field{ // 辞書のエントリ: 1つの大域変数を表す
      private int _type_id;         // 型
      private int _reference_index; // 定数プールにおける大域変数参照の格納先スロット番号

      private int _name_index;       // 定数プールにおける変数名の格納先スロット番号
      private int _descriptor_index; // 定数プールにおける型の格納先スロット番号

      Field(int type_id, String name){ // コンストラクタ
	_type_id          = type_id;
	_name_index       = _constant_pool.putUtf8(name);
	_descriptor_index = _constant_pool.putUtf8(typeDescriptor(type_id));
	_reference_index  =
	  _constant_pool.putFieldref(_name_index, _descriptor_index);
	if (containsKey(name)){
	  throw new CompileError("Field Declared Twice");
	}
	else{
	  put(name, this);
	}
      }

      Variable createReference(Node parent){ // 大域変数参照を生成
	return (new GlobalVariable(parent, _type_id, _reference_index));
      }

      // コード生成: バイトコードではなくfieldsのエントリ
      void emitCode(DataOutputStream classfile) throws IOException{
	classfile.writeShort(0xa); // access_flags = ACC_STATIC | ACC_PRIVATE
	classfile.writeShort(_name_index);
	classfile.writeShort(_descriptor_index);
	classfile.writeShort(0); // attributes_count
      }
    }

    void put(int type_id, String name){ // 大域変数を辞書に登録する
      if (containsKey(name)){
	throw (new CompileError("Field Declared Twice"));
      }
      else{
	put(name, new Field(type_id, name));
      }
    }

    // 名前がnameの大域変数が登録されているなら参照を生成
    Variable createReference(Node parent, String name){
      Field field = (Field)(get(name));

      return ((field == null) ? null : (field.createReference(parent)));
    }

    // コード生成: fields
    void emitCode(DataOutputStream classfile) throws IOException{
      Enumeration fields = elements();
      int size = size();

      if (size > 65535){
	throw (new IOException("Too Big Classfile"));
      }
      classfile.writeShort(size);
      while(fields.hasMoreElements()){
	((Field)(fields.nextElement())).emitCode(classfile);
      }
    }
  }

  // コンパイル対象の関数群を格納する辞書
  private final class Methods extends Hashtable{
    private class Function extends Scope{ // コンパイル対象の関数を表す中間語
      private String _filename;
      private int    _return_type;
      private int    _reference_index;

      private int    _name_index;
      private int    _descriptor_index;
      private Block  _code;

      Function(int return_type, String name) throws IOException{
	super(null); // 構文解析: 関数定義とは返戻値型return_type，関数名nameに
	_filename = _tokenstream.getFileName();
	_return_type = return_type;
	_name_index  = _constant_pool.putUtf8(name);
	_descriptor_index =
	    _constant_pool.putUtf8(parseParameters(name)); // 引数宣言群が続き
	_reference_index  =
	  _constant_pool.putMethodref(_name_index, _descriptor_index);
	if ((_tokenstream.currentToken() == R_PARENTHESIS) && // 更に')'と
	    (_tokenstream.nextToken() == L_BRACE)){    // Blockが続くものである
	  _code = new Block(this);
	}
	else{
	  throw (new CompileError("Parenthesis Mismatch"));
	}
      }

      // 引数宣言群の構文解析: 返戻値はディスクリプタ(引数および返戻値の型)
      private String parseParameters(String name) throws IOException{
	StringBuffer descriptor = new StringBuffer("(");
	int token = _tokenstream.nextToken();
	String key;

	if (token != R_PARENTHESIS){
	  while(token == TYPE_int){            // 構文解析: 引数宣言群は型に
	    descriptor.append(typeDescriptor(token));
	    if (_tokenstream.nextToken() == IDENTIFIER){ // 識別子が続き
	      putLocalVariable(token, _tokenstream.getIdentifier());
	      if ((token = _tokenstream.nextToken()) == R_PARENTHESIS){ // ')'がくるまで
		break;
	      }
	      else if (token == COMMA){ // ','がきて，更に次の引数宣言が続く
	        token = _tokenstream.nextToken();
		continue;
	      }
	    }
	    throw (new CompileError("Invalid Parameter"));
	  }
	}
	descriptor.append(")");
	if (containsKey(key = name + descriptor.toString())){
	  throw (new CompileError("Function Declared Twice"));
	}
	put(key, this);
	descriptor.append(typeDescriptor(_return_type));

	return (descriptor.toString());
      }

      Expression parseReferenceOrCall(Node parent, // 識別子から先の構文解析
				      String name) throws IOException{
	Expression result;

	if (((result = createReference(parent, name)) == null) &&
	    ((result = _fields.createReference(parent, name)) == null)){
	  // nameが局所変数でも大域変数でないなら，関数呼出しのはず
	  result = new CallExpression(parent, name);
	}

	return (result);
      }

      String getFileName(){
	return (_filename);
      }

      int getMethodReturnType(){
	return (_return_type);
      }

      int getReferenceIndex(){
	return (_reference_index);
      }

      void emitCode(DataOutputStream classfile) throws IOException{ // コード生成
	classfile.writeShort(9); // access_flags = ACC_PUBLIC | ACC_STATIC
	classfile.writeShort(_name_index);
	classfile.writeShort(_descriptor_index);
	classfile.writeShort(1); // 属性の数: Code Attribute(関数の本体)のみなので1

	if (!(_code.emitCode(_code_buffer))){ // バイトコードを_code_bufferに格納
	  if (_return_type == TYPE_void){
	    _code_buffer.writeUnsignedByte(BC_return);
	  }
	  else{
	    throw (new CompileError("Return is not at the end", this));
	  }
	}
	_code_buffer.flush(classfile); // Code Attribute(バイトコード他)を出力
      }
    }

    void parse_and_put(int return_type, String name) throws IOException{
      new Function(return_type, name);
    }

    boolean resolve(CallExpression call){ // callの呼出先はコンパイル対象？
      Function method = (Function)(get(call.getIdentifier()));
      boolean result;

      if (result = (method != null)){
	call.patch(method.getMethodReturnType(), method.getReferenceIndex()); 
      }

      return (result);
    }

    void emitCode(DataOutputStream classfile) throws IOException{ // コード生成
      Enumeration methods = elements();
      int size = size();

      if (size > 65535){
	throw (new IOException("Too Big Classfile"));
      }
      classfile.writeShort(size);
      while(methods.hasMoreElements()){
	((Function)(methods.nextElement())).emitCode(classfile);
      }
    }
  }

  // ライブラリが提供する関数群を登録した辞書
  private final class Library extends Hashtable{
    private class LibraryMethod{ // 辞書に登録するライブラリ関数のエントリ
      private int _return_type;
      private int _reference_index;

      LibraryMethod(String name, String descriptor, int return_type){
	int class_index = _constant_pool.putClass(LIBRARY_NAME);
	int name_index = _constant_pool.putUtf8(name);
	int descriptor_index = _constant_pool.putUtf8(descriptor);

	_return_type = return_type;
	_reference_index =
	  _constant_pool.putMethodref(class_index,
				      name_index, descriptor_index);
      }

      int getMethodReturnType(){
	return (_return_type);
      }

      int getReferenceIndex(){
	return (_reference_index);
      }
    }

    private int convertType(Class from){
      int to = TYPE_invalid;

      if (from == Integer.TYPE){
	to = TYPE_int;
      }
      else if (from == Void.TYPE){
	to = TYPE_void;
      }

      return (to);
    }

    private void put(Method method){ // 辞書にライブラリ関数を登録する処理
      int modifiers = method.getModifiers();

      if ((Modifier.isPublic(modifiers)) && (Modifier.isStatic(modifiers))){
	Class[] parameter_types = method.getParameterTypes();
	StringBuffer descriptor = new StringBuffer("(");
	String name = method.getName();
	String key;
	int type;

	for(int i=0; i<parameter_types.length; i++){
	  switch(type = convertType(parameter_types[i])){
	  case TYPE_int:
	    break;
	  default:
	    return;
	  }
	  descriptor.append(typeDescriptor(type));
	}
	descriptor.append(")");
	key = name + descriptor.toString();
	switch(type = convertType(method.getReturnType())){
	case TYPE_int:
	case TYPE_void:
	  break;
	default:
	  return;
	}
	descriptor.append(typeDescriptor(type));
	put(key, new LibraryMethod(name, descriptor.toString(), type));
      }
    }

    // コンストラクタ: LIBRARY_NAMEが指定するクラス内のライブラリ関数一式を登録
    Library() throws ClassNotFoundException{
      Method[] methods = (Class.forName(LIBRARY_NAME)).getDeclaredMethods();

      for(int i=0; i<methods.length; i++){
	put(methods[i]);
      }
    }

    // callの呼出先がライブラリにあるか検索する
    boolean resolve(CallExpression call){
      LibraryMethod method = (LibraryMethod)(get(call.getIdentifier()));
      boolean result;

      if (result = (method != null)){
	call.patch(method.getMethodReturnType(), method.getReferenceIndex()); 
      }

      return (result);
    }
  }

  // コンパイル済みコードの一時格納先
  private class CodeBuffer{
    private int _attribute_name_index; // 定数プールにおける属性名"Code"の登録先スロット番号
    private byte[] _codes; // バイトコード格納用配列

    int _max_stack;  // コードが使用するオペランドスタックの最大長
    int _max_locals; // コードが使用する局所変数の最大数
    int _pc;         // _codesに格納済みのバイトコードのバイト数

    CodeBuffer(){ // コンストラクタ
      _attribute_name_index = _constant_pool.putUtf8("Code");
      _codes = new byte[65536];
      clear();
    }

    private void clear(){
      _max_locals = 0;
      _max_stack = 0;
      _pc = 0;
    }

    // CodeBufferに一時的にバッファした内容をclassfileに出力，消去する．
    void flush(DataOutputStream classfile) throws IOException{
      classfile.writeShort(_attribute_name_index);
      classfile.writeInt(_pc + 12); // attribute_length
      classfile.writeShort(_max_stack);
      classfile.writeShort(_max_locals);
      classfile.writeInt(_pc);
      classfile.write(_codes, 0, _pc);
      classfile.writeShort(0); // exceptions_table_length
      classfile.writeShort(0); // attributes_count
      clear();
    }

    void setMaxStack(int max_stack) throws IOException{
      if ((max_stack > _max_stack) &&
	  ((_max_stack = max_stack) > 65535)){
	throw (new IOException("Too Deep Operand Stack"));
      }
    }

    void setMaxLocals(int max_locals) throws IOException{
      if ((max_locals > _max_locals) &&
	  ((_max_locals = max_locals) > 65535)){
	throw (new IOException("Too Many Local Variables"));
      }
    }

    int pc(){
      return (_pc);
    }

    private void extendCode(int size){ // 必要に応じて_code領域を拡張する
      if (_pc+size > _codes.length){
	byte[] new_codes =
	  new byte[Math.max(_codes.length, size) + _codes.length];
	System.arraycopy(_codes, 0, new_codes, 0, _pc);
	_codes = new_codes;
      }
    }

    void insert(int offset, int size){ // _codesのoffset番目に長さsizeの空領域を挿入
      extendCode(size);
      System.arraycopy(_codes, offset, _codes, offset + size, _pc - offset);
      _pc += size;
    }

    int commit(int size){ // _codeの_pc番目から先にsizeの空領域を挿入
      int result = _pc;

      extendCode(size);
      _pc += size;

      return (result);
    }

    // patch*: _codesのoffset番目にdataを書き込む．バックパッッチ用．
    void patchUnsignedByte(int offset, int data) throws IOException{
      if ((0 <= data) && (data <=255)){
	_codes[offset+0] = (byte)(data);
      }
      else{
	throw (new IOException("Value Out Of Range"));
      }
    }

    void patchShort(int offset, int data) throws IOException{
      if ((Short.MIN_VALUE <= data) && (data <= Short.MAX_VALUE)){
	_codes[offset+0] = (byte)(data >> 8);
	_codes[offset+1] = (byte)(data);
      }
      else{
	throw (new IOException("Value Out Of Range"));
      }
    }

    void patchInt(int offset, int data){
      _codes[offset+0] = (byte)(data >> 24);
      _codes[offset+1] = (byte)(data >> 16);
      _codes[offset+2] = (byte)(data >> 8);
      _codes[offset+3] = (byte)(data & 0xFF);
    }

    // write*: _codesの_pc番目にdataを書き込む
    private void writeRawUnsignedByte(int data){
      extendCode(1);
      _codes[_pc++] = (byte)data;
    }

    void writeUnsignedByte(int data) throws IOException{
      extendCode(1);
      patchUnsignedByte(_pc++, data);
    }

    void writeUnsignedShort(int data) throws IOException{
      if ((0 <= data) && (data <=65535)){
	writeRawUnsignedByte(data >> 8);
	writeRawUnsignedByte(data);
      }
      else{
	throw (new IOException("Value Out Of Range"));
      }
    }

    void writeByte(int data) throws IOException{
      if ((Byte.MIN_VALUE <= data) && (data <= Byte.MAX_VALUE)){
	writeRawUnsignedByte(data);
      }
      else{
	throw (new IOException("Value Out Of Range"));
      }
    }

    void writeShort(int data) throws IOException{
      extendCode(2);
      patchShort(_pc, data);
      _pc += 2;
    }

    void writeInt(int data){
      extendCode(4);
      patchInt(_pc, data);
      _pc += 4;
    }
  }

  // ソースファイルを読込み，中間表現に変換して辞書に登録する処理
  private void parseFile(String filename) throws IOException{
    int token;

    _tokenstream = new TokenStream(filename);
    while((token = _tokenstream.nextToken()) != EOF){
      switch(token){
      case TYPE_int:          // int型の宣言: 大域変数か関数
	if (_tokenstream.nextToken() == IDENTIFIER){
	  String name = _tokenstream.getIdentifier();
	  switch(_tokenstream.nextToken()){
	  case SEMICOLON:     // 大域変数なら_field辞書に登録
	    _fields.put(token, name);
	    continue;
	  case L_PARENTHESIS: // 関数なら中間表現を生成して_method辞書に登録
	    _methods.parse_and_put(token, name);
	    continue;
	  }
	}
	break;
      case TYPE_void:         // void型の宣言: 関数
	if (_tokenstream.nextToken() == IDENTIFIER){
	  String name = _tokenstream.getIdentifier();
	  if (_tokenstream.nextToken() == L_PARENTHESIS){
	    _methods.parse_and_put(token, name); //中間表現を生成して_method辞書に登録
	    continue;
	  }
	}
      }
      // 大域変数宣言でも関数定義でもないので，エラー
      throw (new CompileError("Invalid Declaration"));
    }
  }

  // コンストラクタ: コンパイラの初期化とソースファイル群の中間表現への変換
  private Chavac(String[] args) throws ClassNotFoundException, IOException{
    String this_classname;
    int i; // 解釈済みのコマンドライン引数の数

    // コンパイルオプションの処理
    if (args[0] == "-o"){
      this_classname = args[1];
      i = 2;
    }
    else{
      this_classname = "A";
      i = 0;
    }
    _classfile_name = this_classname + ".class";

    // 初期化: 空の辞書の生成など
    _constant_pool  = new ConstantPool();
    _library        = new Library();
    _code_buffer    = new CodeBuffer();
    _this_class     = _constant_pool.putClass(this_classname);
    _super_class    = _constant_pool.putClass("java/lang/Object");
    _fields         = new Fields();
    _methods        = new Methods();

    /* コマンドラインで指定したソースファイルを順次読み込み，
     * 字句解析，構文解析，意味解析を適用して中間表現に変換
     */
    while(i<args.length){
      parseFile(args[i++]);
    }
  }

  // コード生成用の補助メソッド群
  private static String typeDescriptor(int type_id){
    switch(type_id){
    case TYPE_int:
      return ("I");
    case TYPE_void:
      return ("V");
    default:
      throw (new Error("No Such Type"));
    }
  }

  private void emitCode() throws IOException{	// クラスファイルの出力
    DataOutputStream classfile =
      new DataOutputStream(new FileOutputStream(_classfile_name));

    classfile.writeInt(0xcafebabe); // magic
    classfile.writeShort(0x03); // minor_version
    classfile.writeShort(0x2d); // major_version
    _constant_pool.emitCode(classfile);
    classfile.writeShort(0x20); // access_flags
    classfile.writeShort(_this_class);
    classfile.writeShort(_super_class);
    classfile.writeShort(0); // interfaces_count
    _fields.emitCode(classfile);
    _methods.emitCode(classfile);
    classfile.writeShort(0); // attributes_count
  }

  // mainメソッド
  public static void main(String[] args){
    try{
      (new Chavac(args)).emitCode();
    }
    catch(Exception error){
      System.out.println(error.getMessage());
    }
  }
}
