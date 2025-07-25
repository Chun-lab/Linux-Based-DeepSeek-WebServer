# Linux-based-DeepSeek-Webserver

## 基于Linux和DeepSeek的AI聊天服务器

这是一个简单的聊天网页应用程序，包含登录、注册、聊天功能，并且处理登录失败和注册失败的情况。以下是项目的主要功能和页面截图。

使用注意事项：mysql默认的账户密码在main.cpp中，需要调整服务器端对应的配置

需要在ChatBot.cpp文件中添加自己的gpt-key

## 页面展示

### 登录或注册页面

![登录页面](resources/img_readme/登录界面.png)

- 用户可以在此页面输入用户名和密码进行登录。

### 注册页面

![注册页面](resources/img_readme/注册界面.png)

- 新用户可以在此页面输入相关信息进行注册。

### 登录失败页面

<img src="resources/img_readme/登陆失败.png" width="461" height="351" alt="登陆失败">

- 当用户输入错误的用户名或密码时，显示登录失败提示。

### DeepSeek聊天页面

<img src="resources/img_readme/deepseek.png" width="461" height="481" alt="deepseek">

- 用户登录后，可以在此页面DeepSeek大模型进行聊天访问。
