from openai import OpenAI
import json

# Point to the local server
client = OpenAI(base_url="http://localhost:1234/v1", api_key="lm-studio")
Model = "deepseek/deepseek-r1-0528-qwen3-8b"
# 初始化对话历史
messages = [
    {"role": "system", "content": "You are a software engineer"}
]

def chat_with_stream():
    while True:
        # 获取用户输入
        user_input = input("[User Prompt]: ")
        if user_input.lower() in ["exit", "quit", "bye"]:
            break
        
        # 添加用户消息到历史记录
        messages.append({"role": "user", "content": user_input})
        
        # 发送流式请求
        response = client.chat.completions.create(
            model=Model,
            messages=messages,
            temperature=0.7,
            stream=True
        )

        # 实时显示模型回复
        print("Answer: ", end="")
        assistant_reply = ""
        for chunk in response:
            if chunk.choices[0].delta.content:
                content = chunk.choices[0].delta.content
                print(content, end="", flush=True)
                assistant_reply += content
        print()  # 换行
        
        # 将模型回复添加到历史记录
        messages.append({"role": "assistant", "content": assistant_reply})

def save_history_message(filename):
    with open(filename, "w") as json_file:
        json.dump(messages, json_file, indent = 4)


if __name__ == "__main__":
    print("Start Conversion（Input exit/quit/bye to terminate the conversion）")
    chat_with_stream()
    # save the history messages;
    filename = "topic1.json"
    save_history_message(filename)
