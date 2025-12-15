module full_adder (
  input a,
  input b,
  input cin,
  output sum,
  output cout
);

  wire w1, w2, w3;

  // Sum logic
  xor g1(w1, a, b);
  xor g2(sum, w1, cin);

  // Carry out logic
  and g3(w2, a, b);
  and g4(w3, w1, cin);
  or  g5(cout, w2, w3);

endmodule