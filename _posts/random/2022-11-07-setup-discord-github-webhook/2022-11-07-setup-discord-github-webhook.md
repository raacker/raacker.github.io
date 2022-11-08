---
title: "Setup Discord & Github Webhook"
last_modified_at: 2022-11-07T20:00:00-08:00
categories:
    - random
tags:
    - [random]
excerpt: "How to add github notifications into your discord channels"
---

Better do it than keep talking. Let's go straight.

## 1. Setup discord channel

Go to **Edit Channel**

![](/_posts/random/2022-11-07-setup-discord-github-webhook/images/setup1.png)

-> **Integrations**

![](/_posts/random/2022-11-07-setup-discord-github-webhook/images/setup2.png)

-> **Create Webhooks**

![](/_posts/random/2022-11-07-setup-discord-github-webhook/images/setup3.png)

Then just name it whatever you want and click *Save Changes*.

Click "Copy Webhook URL" to copy into clipboard.

## 2. Setup webhook in Github

Go to **Settings** -> **Webhooks**

![](/_posts/random/2022-11-07-setup-discord-github-webhook/images/setup4.png)

Click **Add webhook** button.

![](/_posts/random/2022-11-07-setup-discord-github-webhook/images/setup5.png)


For the Payload URL, just paste the discord URL but append **/github** on the back.

The Content Type should be **application/json**.

If you want to notify only specific events, select *Let me select individual events*

![](/_posts/random/2022-11-07-setup-discord-github-webhook/images/setup6.png)

As a result,

![](/_posts/random/2022-11-07-setup-discord-github-webhook/images/setup7.png)

Happy Hacking!