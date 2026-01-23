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
  // ???C?u???????(println()???)??????N???X??
  private static final String LIBRARY_NAME = "Chava";

  // ?g?[?N????\?????Q
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

  // Java??o?C?g?R?[?h??????????Q
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

  private TokenStream  _tokenstream;    // ??????n
  private Library      _library;        // ???C?u????
  private CodeBuffer   _code_buffer;    // ?R???p?C?????R?[?h????i?[??
  private String       _classfile_name; // ?o??N???X?t?@?C????

  private ConstantPool _constant_pool;  // ???v?[??
  private int _this_class;       // ???v?[?????????o??N???X????o?^??X???b?g???
  private int _super_class;      // ???v?[?????????e?N???X????o?^??X???b?g???
  private Fields       _fields;	 // ????\?[?X?R?[?h????`???????????o?^??????
  private Methods      _methods; // ????\?[?X?R?[?h????`?????????o?^??????

  // ?R???p?C???G???[
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

  // ??????n?F???????????g?[?N???????ïì????
  private class TokenStream extends BufferedReader{
    private String _filename;	   // ????t?@?C????
    private String _line;	   // ???????s
    private int    _line_no;	   // ???????s???
    private int    _max_index;	   // ???????s??????????
    private int    _current_index; // ???????s???????C???????????????u
    private int    _current_token; // ?????????g?[?N??
    private String _identifier;	   // ????????????q??l(??????)
    private long   _int_value;	   // ??????????????l

    // ?R???X?g???N?^: ??????n????????????????
    TokenStream(String filename) throws IOException{
      super(new FileReader(filename));
      _filename = filename;
      _line_no  = 0;
      readNextLine();
    }

    // ????s??????????: ??s???????
    private void readNextLine() throws IOException{
      while((_line = readLine()) != null){
	_line_no++;
	if ((_max_index = _line.length()) > 0){	// ??s???????
	  _current_index   = 0;	// ???????????????u???s????????
	  break;		// ????????
	}
      }
    }

    private char nextChar(){ // ??????????????????ËY??
      if (_current_index < _max_index){
	return (_line.charAt(_current_index));
      }
      else{
	return (' ');
      }
    }

    int nextToken() throws IOException{ // ????g?[?N??????????????ËY??
      char next_character;

      if (_line == null){ // ?S???s??????????EOF????
	return (_current_token = EOF);
      }

      do{ // ????????????
	if (_current_index == _max_index){
	  readNextLine();
	  if (_line == null){ // ?S???s??????????EOF????
	    return (_current_token = EOF);
	  }
	}
	next_character = _line.charAt(_current_index++); // ??????????????
      }while(Character.isWhitespace(next_character));

      switch(next_character){ // ??????????????g?[?N??????o??
      case DIVIDE:                                       // '/'
	if (nextChar() == DIVIDE){ // '/'??2?????????R?????g
	  readNextLine();          // ?R?????g???????????
	  return (nextToken());    // ?????????R?????g?????g?[?N??????
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
	if (Character.isLetter(next_character)){        // ?p??(?p??|????)*
	  int begin_index = _current_index - 1;
	  while(Character.isLetterOrDigit(nextChar())){
	    _current_index++;
	  }
	  _identifier =
	    (_line.substring(begin_index, _current_index)).intern();
	  if (_identifier == "int"){                    // ?\????m?F
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
	    return (_current_token = IDENTIFIER); // ?\????????????q
	  }
	}
	else if (Character.isDigit(next_character)){    // ????+
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
	  throw (new CompileError("Invalid Character")); // ???????????G???[
	}
      }
    }

    int currentToken(){     // ?????????g?[?N?????????
      return (_current_token);
    }

    String getFileName(){   // ????t?@?C???????????
      return (_filename);
    }

    String getIdentifier(){ // ????????????q??l???????
      return (_identifier);
    }

    int getIntValue(){      // ??????????????l???????
      return ((int)(_int_value));
    }

    int getLineNo(){        // ?????????s??????????
      return (_line_no);
    }
  }

  // ???????`(?\?????C??????C?R?[?h????)?D????\?????\????????D
  private class Node{     // ?S??????e?N???X
    private Node _parent; // ?e?m?[?h?D???????a+b?????\????C+??a?????b??e
    int _line_no;         // ?m?[?h(this)????????\?[?X?R?[?h??s???

    Node(Node parent){    // ?R???X?g???N?^?D?????o???_parent??_line_no????
      setParent(parent);
      _line_no = _tokenstream.getLineNo();
    }

    final void setParent(Node parent){
      _parent = parent;
    }

    String getFileName(){    // ?m?[?h????????\?[?X?R?[?h??t?@?C???????èÔ
      return (_parent.getFileName()); // default?????: ?m?????????e?????
    }

    int getLineNo(){
      return (_line_no);
    }

    int localVariableCount(){ // ?m?[?h????????Scope??L???????????????èÔ
      return (_parent.localVariableCount());
    }

    int getMethodReturnType(){ // ?m?[?h???????àË?\?b?h????l?^???èÔ
      return (_parent.getMethodReturnType());
    }

    Expression parseReferenceOrCall(Node parent,
				    String name) throws IOException{
      // ????q??????\?????: ??? or ??????C??????????o??
      return (_parent.parseReferenceOrCall(parent, name));
    }

    final Statement parseStatement(int token) throws IOException{
      // ????\?????: ????g?[?N??????C???????????C???????R???X?g???N?^?????
      switch(token){
      case L_BRACE:                    // '{' ????????u???b?N??
	return (new BlockStatement(this));
      case IDENTIFIER:                 // ????q????????????o?????????
      {
	Expression first_term =
	  parseReferenceOrCall(this, _tokenstream.getIdentifier());

	return (first_term.parseSuccessorStatement(this));
      }
      case IF:                         // if????????if??
	return (new IfStatement(this));
      case WHILE:                      // while????????while??
	return (new WhileStatement(this));
      case RETURN:                     // return????????return??
	return (new ReturnStatement(this));
      default:                         // ???????????G???[
	throw (new CompileError("Invalid Statement"));
      }
    }

    final Statement parseStatement() throws IOException{ // ????\?????
      return (parseStatement(_tokenstream.nextToken()));
    }

    /* ????\?????
     *
     * ????\???????????\?????????Q????????D
     *
     * ????null_is_candidate??C??????????(null)??????\??????
     * ??????????D???????????o????'func('??????C????????
     * ??????????í¡??????????????C??????????('func()')???D
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

  private abstract class Expression extends Node{ // ????\???S??????e?N???X

    Expression(Node parent){
      super(parent);
    }

    Statement parseSuccessorStatement(Node parent) throws IOException{
      throw (new CompileError("Shoud Not Reach Here"));
    }

    // ????v?Z?????^?????I?R?[?h??buffer??o?????D
    abstract int emitRCode(CodeBuffer buffer, int sp) throws IOException;
  }

  private abstract class Variable extends Expression{ // ?????\???????
    int     _type_id;  // ?????^

    Variable(Node parent, int type_id){
      super(parent);
      _type_id  = type_id;
    }

    // ???g???????????Q?????m?[?h???????D
    abstract Variable createReference(Node parent);

    // ?????????Q??????(????????)????????\????????
    Statement parseSuccessorStatement(Node parent) throws IOException{
      return (new SubstituteStatement(parent, this));
    }

    abstract void emitCode(CodeBuffer buffer,
			   boolean is_load) throws IOException;

    // ?????l??????????R?[?h???o?????
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

  private class GlobalVariable extends Variable{ // ???????\???????
    private int _reference_index; // ???v?[?????????????????o?^??X???b?g???

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

  private class LocalVariable extends Variable{ // ????????\???????
    private int _index; // ?X?^?b?N?t???[????????????????i?[??X???b?g???

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

  private class ConstantInt extends Expression{ // ??????\???????
    private int _value; // ??????l
    private int _index; // ???v?[?????????????o?^??X???b?g???

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

  private class UnaryOperator extends Expression{ // ?P?????Z?q??\???????
    private int _operator;          // ?P?????Z?q????: + or -
    private Expression _expression; // ?P?????Z?q???????

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

  private class BinaryOperator extends Expression{ // ????Z?q??\???????
    private int _operator;                // ?j?????Z?q????: +, -, *, /
    private Expression _left_expression;  // ?j?????Z?q????????
    private Expression _right_expression; // ?j?????Z?q??E?????

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

  private class CallExpression extends Expression{ // ?????o????\???????
    private String _name;         // ?????
    private Vector _arguments;    // ??????
    private String _identifier;   // ????? + ???????????l?^
    private int _return_type;     // ???l?^
    private int _reference_index; // ???v?[??????????o???\?b?h??o?^?X???b?g???

    CallExpression(Node parent,
		   String name) throws IOException{
      super(parent);
      _name = name;                   // ?\?????: ?????o????????qname??
      _arguments = new Vector();

      if (_tokenstream.nextToken() == L_PARENTHESIS){ // '('??????
	Expression argument = parseExpression(true);  // ?C???????????????

	if (argument != null){
	  _arguments.addElement(argument);
	  while(_tokenstream.currentToken() == COMMA){
	    _arguments.addElement(parseExpression(false));
	  }
	}

	if (_tokenstream.currentToken() == R_PARENTHESIS){ // ????')'?????????????
	  _identifier = null;          // ???l?^??C???????????????u
	  _return_type = TYPE_invalid;
	  _reference_index = 0;
	  return;                      // ?????\???????I???????????
	}
      }

      throw (new CompileError("Parse Error in Call")); // ?????????G???[
    }

    // ?îK??o????\?????
    Statement parseSuccessorStatement(Node parent) throws IOException{
      return (new CallStatement(parent, this));
    }

    final String getIdentifier(){
      return (_identifier);
    }

    final void patch(int return_type, int reference_index){
      _return_type = return_type;         // ???l?^????v?[??????????o??
      _reference_index = reference_index; // ???\?b?h??o?^?X???b?g???????
    }

    int emitRCode(CodeBuffer buffer, int sp) throws IOException{
      // identifier?????
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

      // identifier???v?????o?????????_return_type??_reference_index?????
      if (!(_methods.resolve(this) || _library.resolve(this))){
	throw (new CompileError("Function Not Found", this));
      }

      // ?R?[?h??o??
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

  private abstract class Statement extends Node{ // ????\???S??????e?N???X
    Statement(Node parent){
      super(parent);
    }

    abstract boolean emitCode(CodeBuffer buffer) throws IOException;
  }

  private class SubstituteStatement extends Statement{ // ???????\???????
    private Variable   _destination;
    private Expression _source;

    SubstituteStatement(Node parent,
			Variable destination) throws IOException{
      super(parent);
      _destination = destination;     // ?\?????: ??????????destination??
      _destination.setParent(this);
      if (_tokenstream.nextToken() == SUBSTITUTE){      // '=' ??????
	_source = parseExpression(false);               // ?X?????????
	if (_tokenstream.currentToken() == SEMICOLON){  // ????';'?????????????
	  return;                     // ?????\???????I???????????
	}
      }
      throw (new CompileError("Invalid Substitution")); // ?????????G???[
    }

    boolean emitCode(CodeBuffer buffer) throws IOException{ // ?R?[?h????
      if (_source.emitRCode(buffer, 0) != _destination.emitLCode(buffer)){
	throw (new CompileError("Type Mismatch", this));
      }
      return (false);
    }
  }

  private class CallStatement extends Statement{ // ?îK??o????\???????
    private CallExpression _call_expression;

    CallStatement(Node parent,
		  CallExpression call_expression) throws IOException{
      super(parent);           // ?\?????: ?îK??o?????D?????o????n???
      _call_expression = call_expression; 
      _call_expression.setParent(this);
      if (_tokenstream.nextToken() == SEMICOLON){ // ?????';'?????????????
	return;                // ?????\???????I???????????
      }
      throw (new CompileError("Invalid Call")); // ?????????G???[
    }

    boolean emitCode(CodeBuffer buffer) throws IOException{ // ?R?[?h????
      switch(_call_expression.emitRCode(buffer, 0)){
      case TYPE_int:
	buffer.writeUnsignedByte(BC_pop);
      }
      return (false);
    }
  }

  private abstract class ConditionStatement extends Statement{ // ???????????e?N???X
    int _condition;           // ??r???Z?q
    Expression _l_expression; // ??r???Z?q????????
    Expression _r_expression; // ??r???Z?q??E?????
    Statement  _statement;    // ??????????????s????

    ConditionStatement(Node parent) throws IOException{
      super(parent); // ?\?????: ????????????C?????if?????while??????
      if (_tokenstream.nextToken() == L_PARENTHESIS){       // '('??????
	_l_expression = parseExpression(false);             // ????????
	switch(_condition = _tokenstream.currentToken()){   // ??r???Z?q??????
	case CMP_Equal:
	case CMP_NotEqual:
	case CMP_Greater:
	case CMP_GreaterOrEqual:
	case CMP_Less:
	case CMP_LessOrEqual:
	  _r_expression = parseExpression(false);            // ????????
	  if (_tokenstream.currentToken() == R_PARENTHESIS){ // ';'??????
	    _statement = parseStatement();    // ??????????????????
	    return;                           // ?????I???????????
	  }
	default:
	  break;
	}
      }
      throw (new CompileError("Condition Parse Error")); // ?????????G???[
    }
  }

  private class IfStatement extends ConditionStatement{ // if????\???????
    IfStatement(Node parent) throws IOException{
      super(parent);
    }

    boolean emitCode(CodeBuffer buffer) throws IOException{ // ?R?[?h????
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

  private class WhileStatement extends ConditionStatement{ // while????\???????
    WhileStatement(Node parent) throws IOException{
      super(parent);
    }

    boolean emitCode(CodeBuffer buffer) throws IOException{ // ?R?[?h????
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

  private class ReturnStatement extends Statement{ // return????\???????
    private Expression _return_value;              // ???l??????í¡

    ReturnStatement(Node parent) throws IOException{
      super(parent);
      {
	int token;                          // ?\?????: ???\?b?h????l?^??

	if (getMethodReturnType() == TYPE_void){ // void?????l???
	  _return_value = null;
	  token = _tokenstream.nextToken();
	}
	else{                                     // ???????????
	  _return_value = parseExpression(false); // return??????????????
	  token = _tokenstream.currentToken();
	}

	if (token != SEMICOLON){                  // ????';'????????
	  throw (new CompileError("Invalid Return")); // ????????G???[
	}
      }
    }

    boolean emitCode(CodeBuffer buffer) throws IOException{ // ?R?[?h????
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

  private class BlockStatement extends Statement{ // ?u???b?N????\???????
    private Block _block;

    BlockStatement(Node parent) throws IOException{
      super(parent);
      _block = new Block(this);
    }

    boolean emitCode(CodeBuffer buffer) throws IOException{ // ?R?[?h????
      return (_block.emitCode(buffer));
    }
  }

  // ?X?R?[?v(????????L?????C????????????)??\???????
  private abstract class Scope extends Node{
    Hashtable _local_variable_table; // ??????p????????\
    int       _local_variable_count; // ????????V?K?o?^????????????

    Scope(Node parent){
      super(parent);
      _local_variable_table = new Hashtable();
      _local_variable_count =
	(parent == null) ? 0 : parent.localVariableCount();
    }

    void putLocalVariable(int type_id, String name){ // ????????o?^
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
      // ???O??name??????????o?^??????????C?Y??????Q????
      Variable variable = (Variable)(_local_variable_table.get(name));

      return ((variable == null) ? null : (variable.createReference(parent)));
    }

    int localVariableCount(){
      return (_local_variable_count);
    }
  }

  private class Block extends Scope{ // ?u???b?N??\???????
    private Vector _statements;      // ?u???b?N????????????\????i?[??

    Block(Node parent) throws IOException{
      super(parent);
      {
	int token;

	_statements = new Vector();         // ?\?????: ?u???b?N???'{'?????
	while((token = _tokenstream.nextToken()) != R_BRACE){ // '}'????????
	  switch(token){
	  case TYPE_int:
	    parseVariableDeclaration(token);               // ????????
	    break;
	  default:
	    _statements.addElement(parseStatement(token)); // ???????????????
	  }
	}
      }
    }

    private void parseVariableDeclaration(int type_id) throws IOException{
      if (_tokenstream.nextToken() == IDENTIFIER){  // ?\?????: ????????
	String name = _tokenstream.getIdentifier(); // ?^?C????????????
	if (_tokenstream.nextToken() == SEMICOLON){ // ';'?????????????
	  putLocalVariable(type_id, name);          // ?????Block(Scope)??o?^
	  return;                                   // ????I???????????
	}
      }
      throw (new CompileError("Invalid Declaration")); // ?????????G???[
    }

    Expression parseReferenceOrCall(Node parent,    // ????q??????\?????
				    String name) throws IOException{
      Expression result = createReference(parent, name); // ????q????????H

      if (result == null){                                 // ???????????
	result = super.parseReferenceOrCall(parent, name); // ?e????f??????
      }

      return (result);
    }

    boolean emitCode(CodeBuffer buffer) throws IOException{ // ?R?[?h????
      Enumeration statements = _statements.elements();

      buffer.setMaxLocals(localVariableCount());
      while(statements.hasMoreElements()){   // ??????????R?[?h???????o??
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

  // ???v?[??: ?o???N???X?t?@?C??????????Q(?V???{?????)??i?[??
  private final class ConstantPool extends Vector{
    // ???v?[????o?^????v?f????????????g???n?b?V???\?Q
    private Hashtable _class_table;		// ?N???X????
    private Hashtable _name_and_type_table;	// ???O??^??g????
    private Hashtable _integer_table;		// ????????
    private Hashtable _methodref_table;		// ???\?b?h????
    private Hashtable _fieldref_table;		// ?t?B?[???h????
    private Hashtable _utf8_table;		// ?????????

    private abstract class Constant{ // ???v?[????o?^????G???g????e?N???X
      private int _index;

      void setIndex(int index){
	_index = index;
      }

      int getIndex(){
	return (_index);
      }

      // ?R?[?h????: ?N???X?t?@?C??????v?[????G???g??1?????o??
      abstract void emitCode(DataOutputStream classfile) throws IOException;
    }

    private class ConstantClass extends Constant{ // ?N???X??G???g??
      private int _name_index;

      ConstantClass(int name_index){
	_name_index = name_index;
      }

      void emitCode(DataOutputStream classfile) throws IOException{
	classfile.writeByte(7); // CONSTANT_Class
	classfile.writeShort(_name_index);
      }
    }

    private class ConstantNameAndType extends Constant{ // ???O??^??g??G???g??
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

    private class ConstantInteger extends Constant{ // ??????G???g??
      private int _bytes;

      ConstantInteger(int bytes){
	_bytes = bytes;
      }

      void emitCode(DataOutputStream classfile) throws IOException{
	classfile.writeByte(3); // CONSTANT_Integer
	classfile.writeInt(_bytes);
      }
    }

    private class ConstantMethodref extends Constant{ // ???\?b?h??G???g??
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

    private class ConstantFieldref extends Constant{ // ?t?B?[???h??G???g??
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

    private class ConstantUtf8 extends Constant{ // ???????G???g??
      private String _bytes;

      ConstantUtf8(String bytes){
	_bytes = bytes;
      }

      void emitCode(DataOutputStream classfile) throws IOException{
	classfile.writeByte(1); // CONSTANT_Fieldref
	classfile.writeUTF(_bytes);
      }
    }

    ConstantPool(){ // ?R???X?g???N?^: ?????p?n?b?V???\?Q?????
      _class_table         = new Hashtable();
      _name_and_type_table = new Hashtable();
      _integer_table       = new Hashtable();
      _methodref_table     = new Hashtable();
      _fieldref_table      = new Hashtable();
      _utf8_table          = new Hashtable();
    }

    private int put(Hashtable table, Object key, Constant element){ // ?G???g????o?^
      int result;

      table.put(key, element);
      addElement(element);
      element.setIndex(result = size());

      return (result);
    }

    private Integer createKey(int index){ // ?n?b?V???\???o?^??g?????????
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

    int putClass(String name){ // ?N???X??o?^
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

    int putInteger(int value){ // ??????o?^
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
		     int name_index, int descriptor_index){ // ???\?b?h??o?^
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

    int putFieldref(int name_index, int descriptor_index){ // ?t?B?[???h??o?^
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

    int putUtf8(String utf8){ // ???????o?^
      Constant entry = (Constant)(_utf8_table.get(utf8));

      if (entry == null){
	return (put(_utf8_table, utf8, new ConstantUtf8(utf8)));
      }
      else{
	return (entry.getIndex());
      }
    }

    // ?R?[?h????: ?N???X?t?@?C??????v?[?????????????
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

  private final class Fields extends Hashtable{ // ??????Q???i?[??????
    private class Field{ // ??????G???g??: 1?????????\??
      private int _type_id;         // ?^
      private int _reference_index; // ???v?[??????????????Q???i?[??X???b?g???

      private int _name_index;       // ???v?[???????????????i?[??X???b?g???
      private int _descriptor_index; // ???v?[?????????^??i?[??X???b?g???

      Field(int type_id, String name){ // ?R???X?g???N?^
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

      Variable createReference(Node parent){ // ??????Q????
	return (new GlobalVariable(parent, _type_id, _reference_index));
      }

      // ?R?[?h????: ?o?C?g?R?[?h?????fields??G???g??
      void emitCode(DataOutputStream classfile) throws IOException{
	classfile.writeShort(0xa); // access_flags = ACC_STATIC | ACC_PRIVATE
	classfile.writeShort(_name_index);
	classfile.writeShort(_descriptor_index);
	classfile.writeShort(0); // attributes_count
      }
    }

    void put(int type_id, String name){ // ?????????????o?^????
      if (containsKey(name)){
	throw (new CompileError("Field Declared Twice"));
      }
      else{
	put(name, new Field(type_id, name));
      }
    }

    // ???O??name?????????o?^??????????Q????
    Variable createReference(Node parent, String name){
      Field field = (Field)(get(name));

      return ((field == null) ? null : (field.createReference(parent)));
    }

    // ?R?[?h????: fields
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

  // ?R???p?C?????????Q???i?[??????
  private final class Methods extends Hashtable{
    private class Function extends Scope{ // ?R???p?C??????????\???????
      private String _filename;
      private int    _return_type;
      private int    _reference_index;

      private int    _name_index;
      private int    _descriptor_index;
      private Block  _code;

      Function(int return_type, String name) throws IOException{
	super(null); // ?\?????: ?????`?????l?^return_type?C?????name??
	_filename = _tokenstream.getFileName();
	_return_type = return_type;
	_name_index  = _constant_pool.putUtf8(name);
	_descriptor_index =
	    _constant_pool.putUtf8(parseParameters(name)); // ???????Q??????
	_reference_index  =
	  _constant_pool.putMethodref(_name_index, _descriptor_index);
	if ((_tokenstream.currentToken() == R_PARENTHESIS) && // ?X??')'??
	    (_tokenstream.nextToken() == L_BRACE)){    // Block??????????????
	  _code = new Block(this);
	}
	else{
	  throw (new CompileError("Parenthesis Mismatch"));
	}
      }

      // ???????Q??\?????: ???l??f?B?X?N???v?^(???????????l??^)
      private String parseParameters(String name) throws IOException{
	StringBuffer descriptor = new StringBuffer("(");
	int token = _tokenstream.nextToken();
	String key;

	if (token != R_PARENTHESIS){
	  while(token == TYPE_int){            // ?\?????: ???????Q??^??
	    descriptor.append(typeDescriptor(token));
	    if (_tokenstream.nextToken() == IDENTIFIER){ // ????q??????
	      putLocalVariable(token, _tokenstream.getIdentifier());
	      if ((token = _tokenstream.nextToken()) == R_PARENTHESIS){ // ')'????????
		break;
	      }
	      else if (token == COMMA){ // ','??????C?X????????????????
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

      Expression parseReferenceOrCall(Node parent, // ????q??????\?????
				      String name) throws IOException{
	Expression result;

	if (((result = createReference(parent, name)) == null) &&
	    ((result = _fields.createReference(parent, name)) == null)){
	  // name???????????????????????C?????o??????
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

      void emitCode(DataOutputStream classfile) throws IOException{ // ?R?[?h????
	classfile.writeShort(9); // access_flags = ACC_PUBLIC | ACC_STATIC
	classfile.writeShort(_name_index);
	classfile.writeShort(_descriptor_index);
	classfile.writeShort(1); // ???????: Code Attribute(?????{??)??????1

	if (!(_code.emitCode(_code_buffer))){ // ?o?C?g?R?[?h??_code_buffer??i?[
	  if (_return_type == TYPE_void){
	    _code_buffer.writeUnsignedByte(BC_return);
	  }
	  else{
	    throw (new CompileError("Return is not at the end", this));
	  }
	}
	_code_buffer.flush(classfile); // Code Attribute(?o?C?g?R?[?h??)???o??
      }
    }

    void parse_and_put(int return_type, String name) throws IOException{
      new Function(return_type, name);
    }

    boolean resolve(CallExpression call){ // call???o???R???p?C?????H
      Function method = (Function)(get(call.getIdentifier()));
      boolean result;

      if (result = (method != null)){
	call.patch(method.getMethodReturnType(), method.getReferenceIndex()); 
      }

      return (result);
    }

    void emitCode(DataOutputStream classfile) throws IOException{ // ?R?[?h????
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

  // ???C?u??????????????Q??o?^????????
  private final class Library extends Hashtable{
    private class LibraryMethod{ // ??????o?^?????C?u?????????G???g??
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

    private void put(Method method){ // ????????C?u?????????o?^???ËY??
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

    // ?R???X?g???N?^: LIBRARY_NAME???w????N???X??????C?u???????????o?^
    Library() throws ClassNotFoundException{
      Method[] methods = (Class.forName(LIBRARY_NAME)).getDeclaredMethods();

      for(int i=0; i<methods.length; i++){
	put(methods[i]);
      }
    }

    // call???o?à´???C?u?????????????????
    boolean resolve(CallExpression call){
      LibraryMethod method = (LibraryMethod)(get(call.getIdentifier()));
      boolean result;

      if (result = (method != null)){
	call.patch(method.getMethodReturnType(), method.getReferenceIndex()); 
      }

      return (result);
    }
  }

  // ?R???p?C?????R?[?h????i?[??
  private class CodeBuffer{
    private int _attribute_name_index; // ???v?[?????????????"Code"??o?^??X???b?g???
    private byte[] _codes; // ?o?C?g?R?[?h?i?[?p?z??

    int _max_stack;  // ?R?[?h???g?p????I?y?????h?X?^?b?N????
    int _max_locals; // ?R?[?h???g?p?????????????
    int _pc;         // _codes??i?[????o?C?g?R?[?h??o?C?g??

    CodeBuffer(){ // ?R???X?g???N?^
      _attribute_name_index = _constant_pool.putUtf8("Code");
      _codes = new byte[65536];
      clear();
    }

    private void clear(){
      _max_locals = 0;
      _max_stack = 0;
      _pc = 0;
    }

    // CodeBuffer????I??o?b?t?@???????e??classfile??o??C????????D
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

    private void extendCode(int size){ // ?K?v???????_code?????g??????
      if (_pc+size > _codes.length){
	byte[] new_codes =
	  new byte[Math.max(_codes.length, size) + _codes.length];
	System.arraycopy(_codes, 0, new_codes, 0, _pc);
	_codes = new_codes;
      }
    }

    void insert(int offset, int size){ // _codes??offset???????size??????}??
      extendCode(size);
      System.arraycopy(_codes, offset, _codes, offset + size, _pc - offset);
      _pc += size;
    }

    int commit(int size){ // _code??_pc????????size??????}??
      int result = _pc;

      extendCode(size);
      _pc += size;

      return (result);
    }

    // patch*: _codes??offset????data??????????D?o?b?N?p?b?b?`?p?D
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

    // write*: _codes??_pc????data??????????
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

  // ?\?[?X?t?@?C????????C????\???????????????o?^???ËY??
  private void parseFile(String filename) throws IOException{
    int token;

    _tokenstream = new TokenStream(filename);
    while((token = _tokenstream.nextToken()) != EOF){
      switch(token){
      case TYPE_int:          // int?^???: ??????????
	if (_tokenstream.nextToken() == IDENTIFIER){
	  String name = _tokenstream.getIdentifier();
	  switch(_tokenstream.nextToken()){
	  case SEMICOLON:     // ????????_field??????o?^
	    _fields.put(token, name);
	    continue;
	  case L_PARENTHESIS: // ????????\?????????_method??????o?^
	    _methods.parse_and_put(token, name);
	    continue;
	  }
	}
	break;
      case TYPE_void:         // void?^???: ???
	if (_tokenstream.nextToken() == IDENTIFIER){
	  String name = _tokenstream.getIdentifier();
	  if (_tokenstream.nextToken() == L_PARENTHESIS){
	    _methods.parse_and_put(token, name); //????\?????????_method??????o?^
	    continue;
	  }
	}
      }
      // ???????????????`?????????C?G???[
      throw (new CompileError("Invalid Declaration"));
    }
  }

  // ?R???X?g???N?^: ?R???p?C???????????\?[?X?t?@?C???Q?????\???????
  private Chavac(String[] args) throws ClassNotFoundException, IOException{
    String this_classname;
    int i; // ???????R?}???h???C?????????

    // ?R???p?C???I?v?V?????????
    if (args[0] == "-o"){
      this_classname = args[1];
      i = 2;
    }
    else{
      this_classname = "A";
      i = 0;
    }
    _classfile_name = this_classname + ".class";

    // ??????: ??????????????
    _constant_pool  = new ConstantPool();
    _library        = new Library();
    _code_buffer    = new CodeBuffer();
    _this_class     = _constant_pool.putClass(this_classname);
    _super_class    = _constant_pool.putClass("java/lang/Object");
    _fields         = new Fields();
    _methods        = new Methods();

    /* ?R?}???h???C????w?????\?[?X?t?@?C??????????????C
     * ??????C?\?????C???????K?p???????\??????
     */
    while(i<args.length){
      parseFile(args[i++]);
    }
  }

  // ?R?[?h?????p??????\?b?h?Q
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

  private void emitCode() throws IOException{	// ?N???X?t?@?C????o??
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

  // main???\?b?h
  public static void main(String[] args){
    try{
      (new Chavac(args)).emitCode();
    }
    catch(Exception error){
      System.out.println(error.getMessage());
    }
  }
}
