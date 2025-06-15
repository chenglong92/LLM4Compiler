import webbrowser
import os

def create_svg_from_text(svg_src):
    """通过直接生成SVG文本创建图像"""
    # SVG
    with open(svg_src, 'r', encoding='utf-8') as f:
        svg_content = f.read()
    
    # 打开SVG文件
    open_svg_in_browser(svg_src)

def open_svg_in_browser(file_path):
    """在默认浏览器中打开SVG文件"""
    try:
        absolute_path = os.path.abspath(file_path)
        webbrowser.open(f'file://{absolute_path}')
        print(f"已在浏览器中打开: {absolute_path}")
    except Exception as e:
        print(f"无法打开文件: {e}")

if __name__ == "__main__":
    svg_src = "svg_src.svg"
    create_svg_from_text(svg_src)
