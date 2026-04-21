# --- 設定セクション ---
TARGET = motiana

# コンパイラを clang++ に変更
CXX = clang++

# コンパイルオプション（警告と規格）
CXXFLAGS = -Wall -Wextra -std=c++17

# リンクオプション（ncursesw ライブラリをリンク）
LDFLAGS = -lncursesw

# ソースファイルとオブジェクトファイル
SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)

# --- ルールセクション ---

# 実行ファイルの生成（LDFLAGS を追加）
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

# 個別のコンパイル
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 掃除
clean:
	rm -f $(TARGET) $(OBJS)

.PHONY: clean