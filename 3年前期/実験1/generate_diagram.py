import sys
from pyverilog.vparser.parser import parse
from pyverilog.vparser.ast import ModuleDef, InstanceList, Instance, PortArg
from graphviz import Digraph

def generate_circuit_diagram(verilog_file, output_file='circuit'):
    """Verilogファイルを解析して回路図を生成する"""

    # 1. Verilogファイルを解析してAST（抽象構文木）を生成
    ast, _ = parse([verilog_file])

    # 回路図を描画するためのグラフオブジェクトを初期化
    dot = Digraph(comment='Circuit Diagram')
    dot.attr('node', shape='box', style='rounded') # ノードの形状を設定
    dot.attr(rankdir='LR') # 左から右へ描画

    # 2. ASTから回路情報を抽出
    # ModuleDefノードを探索
    for module in ast.description.children():
        if isinstance(module, ModuleDef):
            # モジュール内の要素を走査
            for item in module.items:
                # インスタンスリスト（ゲートや下位モジュール）の場合
                if isinstance(item, InstanceList):
                    for inst in item.instances:
                        # ゲート（インスタンス）をノードとして追加
                        dot.node(inst.name, inst.module)

                        # ポートの接続を処理
                        for port_arg in inst.portlist:
                            port_name = port_arg.portname
                            arg_name = port_arg.argname

                            # 接続元（arg_name）から接続先（inst.name）へのエッジを追加
                            # arg_nameは入力ポート、inst.nameが出力先のゲート
                            dot.edge(str(arg_name), inst.name, label=port_name)

            # モジュールの出力を処理
            # (簡単のため、ここでは出力ポートに接続されるゲートからのエッジを手動で描画)
            # より高度な解析では、信号の方向を追跡する必要がある
            # 例: sumはg2の出力、coutはg5の出力
            dot.node('sum', 'sum', shape='plaintext')
            dot.node('cout', 'cout', shape='plaintext')
            dot.edge('g2', 'sum')
            dot.edge('g5', 'cout')


    # 3. Graphvizで画像ファイルを生成
    dot.render(output_file, format='png', view=True)
    print(f"✅ 回路図 '{output_file}.png' を生成しました。")


if __name__ == '__main__':
    if len(sys.argv) < 2:
        print("使用法: python generate_diagram.py <verilog_file_path>")
    else:
        verilog_file = sys.argv[1]
        generate_circuit_diagram(verilog_file)