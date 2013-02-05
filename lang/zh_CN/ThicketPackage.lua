-- translation for ThicketPackage

return {
	["thicket"] = "林包",

	["#caopi"] = "霸业的继承者",
	["caopi"] = "曹丕",
	["xingshang"] = "行殇",
	[":xingshang"] = "你可以获得死亡角色的所有牌",
	["fangzhu"] = "放逐",
	[":fangzhu"] = "每当你受到一次伤害后，可令一名其他角色摸X张牌（X为你已损失的体力值），然后该角色将其武将牌翻面",
	["songwei"] = "颂威",
	[":songwei"] = "<b>主公技</b>，其他魏势力角色的判定结果为黑色且生效后，可以令你摸一张牌",
	["songwei:yes"] = "可以让曹丕摸一张牌",
	["xingshang:yes"] = "你可以获得阵亡者的所有手牌和装备牌",
	["@fangzhu"] = "请指定要放逐的对象",

	["#xuhuang"] = "周亚夫之风",
	["xuhuang"] = "徐晃",
	["duanliang"] = "断粮",
	[":duanliang"] = "出牌阶段，你可以将一张黑色牌当【兵粮寸断】使用，此牌必须为基本牌或装备牌；你可以对距离２以内的一名其他角色使用【兵粮寸断】",

	["#menghuo"] = "南蛮王",
	["menghuo"] = "孟获",
	["huoshou"] = "祸首",
	[":huoshou"] = "【南蛮入侵】对你无效；你是任何【南蛮入侵】造成伤害的来源",
	["zaiqi"] = "再起",
	[":zaiqi"] = "摸牌阶段开始时，若你已受伤，你可以放弃摸牌，改为从牌堆顶亮出X张牌（X为你已损失的体力值），你回复等同于其中红桃牌数量的体力，然后将这些红桃牌置入弃牌堆，并获得其余的牌。",
	["#HuoshouTransfer"] = "%from 的锁定技【%arg2】被触发，将 %arg 对 %to 所造成的伤害视为 %from 造成",
	["zaiqi:yes"] = "你可以放弃摸牌并展示牌堆顶的X张牌，X为你已损失的体力值，其中每有一张红桃牌，你回复1点体力，然后将这些红桃牌置入弃牌堆，将其余的牌收入手牌",

	["#zhurong"] = "野性的女王",
	["zhurong"] = "祝融",
	["juxiang"] = "巨象",
	[":juxiang"] = "<b>锁定技</b>，【南蛮入侵】对你无效；若其他角色使用的【南蛮入侵】在结算后置入弃牌堆，你获得之",
	["lieren"] = "烈刃",
	[":lieren"] = "每当你使用【杀】对目标角色造成一次伤害后，可与其拼点，若你赢，你获得该角色的一张牌",
	["lieren:yes"] = "可与受到该伤害的角色拼点：若你赢，你获得对方的一张牌",

	["#sunjian"] = "武烈帝",
	["sunjian"] = "孙坚",
	["yinghun"] = "英魂",
	[":yinghun"] = "回合开始阶段开始时，若你已受伤，你可以选择一项：令一名其他角色摸X张牌，然后弃置一张牌；或令一名其他角色摸一张牌，然后弃置X张牌（X为你已损失的体力值）。",
	["@yinghun"] = "请指定要英魂的对象",
	[":yinghun:"] = "请选择英魂技能的选项:",
	["yinghun:d1tx"] = "摸一张牌，弃置X张",
	["yinghun:dxt1"] = "摸X张牌，弃置一张牌",

	["#lusu"] = "独断的外交家",
	["lusu"] = "鲁肃",
	["haoshi"] = "好施",
	[":haoshi"] = "摸牌阶段摸牌时，你可以额外摸两张牌，若此时你的手牌多于五张，则将一半（向下取整）的手牌交给场上手牌数最少的一名其他角色",
	["dimeng"] = "缔盟",
	[":dimeng"] = "出牌阶段，你可以选择两名其他角色，你弃置等同于这两名角色手牌数差的牌，然后交换他们的手牌。每阶段限一次\
★与官方不同之处；座次在后者(A)先得到另一人(B)的手牌，然后B再得到A的手牌",
	["@haoshi"] = "请选择好施的对象",
	["haoshi:yes"] = "额外摸两张牌，若此时你的手牌超过五张，你必须将一半(向下取整)的手牌交给除你外手牌数最少的一名角色",
	["#Dimeng"] = "%from (原来 %arg 手牌) 与 %to (原来 %arg2 手牌) 交换了手牌",

	["#jiaxu"] = "冷酷的毒士",
	["jiaxu"] = "贾诩",
	["wansha"] = "完杀",
	[":wansha"] = "<b>锁定技</b>，在你的回合，除你以外，只有处于濒死状态的角色才能使用【桃】",
	["weimu"] = "帷幕",
	[":weimu"] = "<b>锁定技</b>，你不能成为黑色锦囊牌的目标",
	["luanwu"] = "乱武",
	[":luanwu"] = "<b>限定技</b>，出牌阶段，可令所有其他角色各选择一项：对与其距离最近的另一名角色使用一张【杀】，或失去1点体力",
	["@chaos"] = "乱武",
	["#WanshaOne"] = "%from 的锁定技【%arg】被触发，只能 %from 自救",
	["#WanshaTwo"] = "%from 的锁定技【%arg】被触发，只有 %from 和 %to 自己才能救 %to",
	["@luanwu-slash"] = "请打出一张杀以响应【乱武】",

	["#dongzhuo"] = "魔王",
	["dongzhuo"] = "董卓",
	["jiuchi"] = "酒池",
	[":jiuchi"] = "你可以将你的一张黑桃手牌当【酒】使用",
	["roulin"] = "肉林",
	[":roulin"] = "<b>锁定技</b>，你对女性角色、女性角色对你使用【杀】时，需连续使用两张【闪】才能抵消",
	["benghuai"] = "崩坏",
	[":benghuai"] = "<b>锁定技</b>，回合结束阶段开始时，若你的体力不是全场最少的(或之一)，你须减1点体力或体力上限",
	["baonue"] = "暴虐",
	[":baonue"] = "<b>主公技</b>，每当其他群雄角色造成一次伤害后，可进行一次判定，若为黑桃，你回复1点体力",
	["@roulin1-jink-1"] = "董卓拥有【肉林】技能，您必须出两张【闪】来闪避",
	["@roulin1-jink-2"] = "董卓拥有【肉林】技能，您还需要出一张【闪】来闪避",
	["@roulin2-jink-1"] = "你拥有【肉林】技能，女性出的【杀】您必须出两张【闪】才能闪避",
	["@roulin2-jink-2"] = "你拥有【肉林】技能，您还需出张【闪】才能闪避",
	[":benghuai:"] = "请选择减体力还是体力上限:",
	["benghuai:hp"] = "体力",
	["benghuai:maxhp"] = "体力上限",
	["baonue:yes"] = "你可进行一次判定，若判定结果为黑桃，则董卓回复一点体力",

-- CV
	["cv:caopi"] = "V7，殆尘，lelek",
	["$xingshang1"] = "汝妻子吾自养之，汝勿虑也",
	["$xingshang2"] = "珠沉玉没，其香犹存",
	["$xingshang3"] = "痛神曜之幽潛，哀鼎俎之虛置",
	["$fangzhu1"] = "罪不至死，赦死从流",
	["$fangzhu2"] = "特赦天下，奉旨回京",
	["$fangzhu3"] = "本自同根生，相煎何太急？",
	["$songwei1"] = "吾主英明(男声)",
	["$songwei2"] = "吾主英明(女声)",
	["~caopi"] = "嗟我白发，生一何早。长吟永叹，怀我圣考。",
	["`caopi"] = "席卷天下，囊括四海，完先人遗志，成大魏霸业！",

	["cv:xuhuang"] = "木津川",
	["$duanliang1"] = "断汝粮草,以绝后路",
	["$duanliang2"] = "焚其辎重,乱其军心",
	["~xuhuang"] = "生遇明主,死亦无憾！",

	["cv:menghuo"] = "墨染の飞猫",
	["$huoshou"] = "南蛮之地，皆我子民",
	["$zaiqi1"] = "吾不服也",
	["$zaiqi2"] = "孔明，汝计穷也",
	["$zaiqi3"] = "敌军势大，吾先退避",
	["~menghuo"] = "粳民之地，再无主矣",

	["cv:zhurong"] = "妙妙",
	["$juxiang"] = "万象奔腾，随吾心意",
	["$lieren1"] = "火神降世，燃尽汝躯",
	["$lieren2"] = "呵呵呵～",
	["$lieren3"] = "神不佑我，唉",
	["~zhurong"] = "大王，火神湮逝，妾身去矣",

	["cv:sunjian"] = "木津川",
	["$yinghun1"] = "同举义兵,戮力一心",
	["$yinghun2"] = "孙文台在此,此贼可诛！",
	["~sunjian"] = "死去何愁无勇将，英魂依旧卫江东",

	["cv:lusu"] = "听雨",
	["$haoshi"] = "公瑾莫忧，吾有余粮",
	["$dimeng1"] = "荆襄九郡，暂借于汝",
	["$dimeng2"] = "歃血为盟，誓不叛之",
	["~lusu"] = "荆襄未还，虽死难安",

	["cv:jiaxu"] = "落凤一箭",
	["$wansha1"] = "汝今势孤，命必绝矣",
	["$weimu1"] = "巧变制敌，谋定而动",
	["$weimu2"] = "算无遗策，不动如山",
	["$luanwu"] = "智乱天下，武逆乾坤",
	["~jiaxu"] = "大势已去，吾不能自保矣",

	["cv:dongzhuo"] = "やまもとみ，冰爷，迷宫女友，裤衩",
	["$jiuchi"] = "醉酒销魂啊",
	["$roulin1"] = "屈我淫威，哈哈",
	["$roulin2"] = "董贼，拿命来",
	["$roulin3"] = "去死吧变态！", -- 女性酒杀董卓时播放
	["$baonue"] = "天下群雄，唯我独尊",
	["$benghuai1"] = "不朽之躯，天却亡我", -- 男
	["$benghuai2"] = "不，不可以的……", -- 女
	["~dongzhuo"] = "吾儿奉先何在？呃...",
	["`dongzhuo"] = "汉室于吾如玩物，诸侯吾视之若豕犬，天下不过囊中之物！",

-- illustrator
	["illustrator:caopi"] = "Sonia Tang",
	["illustrator:lusu"] = "LiuHeng",
	["illustrator:sunjian"] = "LiuHeng",
	["illustrator:menghuo"] = "废柴男",
	["illustrator:zhurong"] = "废柴男",
	["illustrator:dongzhuo"] = "小冷",
	["illustrator:xuhuang"] = "Tuu.",
}
