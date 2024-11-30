#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include "./vertex.cpp"
#include "./utils.cpp"

using namespace std;

const string dot_header_path = "./dot_header.txt";
const string dot_footer_path = "./dot_footer.txt";

int main(int argc, char *argv[])
{
    string graph_data_path; // グラフデータのpath

    // グラフデータファイルのpathを読み込む
    if (argc > 1)
    {
        graph_data_path = argv[1];
    }
    else
    {
        cerr << "Error: No graph data !!" << endl;
        return 0;
    }

    string dot_header = read_file(dot_header_path); // dotファイルのheader
    string dot_footer = read_file(dot_footer_path); // dotファイルのfooter

    string dot_code = dot_header; // dot言語のコード

    vector<Vertex> vtxs; // 頂点テーブル

    // グラフデータを読み取る
    vtxs = read_graph_data(graph_data_path);

    // 頂点をDotコードに変換
    dot_code += "\n";
    for (int i = 0; i < vtxs.size(); i++)
    {
        dot_code += "    " + gen_node_dot(i, to_string(i), (vtxs[i].lambda == "1" ? "doublecircle" : "circle")) + "\n";
    }
    dot_code += "\n    input -> q_0;\n";

    // 頂点の接続関係をDotコードに変換
    dot_code += "\n";
    for (int i = 0; i < vtxs.size(); i++)
    {
        dot_code += vtxs[i].to_str() + "\n";
    }

    dot_code += dot_footer + "\n";

    // Dotファイルを作成
    ofstream file("graph.dot");
    file << dot_code;

    return 0;
}
