#include "graphview.h"

MyGraphicsView::MyGraphicsView()
{
    this->setMouseTracking(true);
    this->setRenderHint(QPainter::Antialiasing);
    this->setStyleSheet("padding:0px;border:0px");

    myGraphicsScene = new QGraphicsScene();
    myGraphicsScene->setBackgroundBrush(Qt::transparent);
    myGraphicsScene->setSceneRect(0,0,1183,875);

    this->setScene(myGraphicsScene);
    this->setFixedSize(1183,875);
    this->move(-5,-45);
    this->show();

    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    root=new MyGraphicsVexItem(QPointF(590,150),10, vexID++);
    myGraphicsScene->addItem(root);
    myGraphicsScene->addItem(root->nameTag);
    vexes.push_back(root);
}

void MyGraphicsView::mousePressEvent(QMouseEvent *event)
{
    if(isCreating){// click anywhere to create a new node
        clearSketch();
        MyGraphicsVexItem* endVex=addVex(event->pos());
        strtVex->nexts.push_back(endVex);
        addLine(strtVex,endVex);
        isCreating=!isCreating;
    }else{
        //click on the node that already exists to change "isCreating"
        bool flag=false;
        for(int i=0;i<vexes.size();i++)
        {
            if(event->pos().rx()>=vexes[i]->center.rx()-20 && event->pos().rx()<=vexes[i]->center.rx()+20 &&
                    event->pos().ry()>=vexes[i]->center.ry()-20 && event->pos().ry()<=vexes[i]->center.ry()+20 &&
                        preVexes.count(vexes[i])!=2)//the node that was clicked on can't has two child nodes
            {
                flag=true;
                strtVex=vexes[i];
                preVexes.push_back(vexes[i]);
            }
        }
        if(flag){
            isCreating=!isCreating;
        }
    }
}

void MyGraphicsView::mouseMoveEvent(QMouseEvent *event){
    if(isCreating){
        clearSketch();
        sketchLine(strtVex->pos() + strtVex->rect().center(), event->pos());
    }
}

MyGraphicsVexItem* MyGraphicsView::addVex(QPointF center, qreal radius)
{
    MyGraphicsVexItem *newVex = new MyGraphicsVexItem(center, radius, vexID++);
    myGraphicsScene->addItem(newVex);
    myGraphicsScene->addItem(newVex->nameTag);
    newVex->showAnimation();
    vexes.push_back(newVex);
    return newVex;
}

MyGraphicsLineItem* MyGraphicsView::addLine(MyGraphicsVexItem *start, MyGraphicsVexItem *end)
{
    MyGraphicsLineItem * line=new MyGraphicsLineItem(start,end);
    myGraphicsScene->addItem(line);
    return line;
}

void MyGraphicsView::sketchLine(QPointF start, QPointF end){
    QGraphicsLineItem *newLine = new QGraphicsLineItem(start.x(), start.y(), end.x(), end.y());
    QPen pen;
    pen.setWidth(3);
    pen.setStyle(Qt::DashLine);
    pen.setBrush(QColor(58, 143, 192, 100));
    pen.setCapStyle(Qt::RoundCap);
    newLine->setPen(pen);
    scene()->addItem(newLine);
    sketchItem = newLine;
}

void MyGraphicsView::clearSketch(){
    if(sketchItem != nullptr){
        scene()->removeItem(sketchItem);
        sketchItem = nullptr;
    }
}
void MyGraphicsView::addAnimation(QTimeLine *ani){
    aniQueue.push_back(ani);
    if(!onAni){
        onAni = true;
        nextAni();
    }
}

void MyGraphicsView::nextAni(){
    if(aniQueue.size() > 0){
        QTimeLine *next = aniQueue.front();
        curAni = next;
        aniQueue.pop_front();
        connect(next, &QTimeLine::finished, [=](){nextAni(); next->deleteLater();});
        next->setDuration(next->duration() / speedRate);
        next->start();
    }
    else{
        onAni = false;
        curAni = nullptr;
    }
}

void MyGraphicsView::buildTree()
{
    for(int i=0;i<vexes.size();i++)
    {
        vexes[i]->setBrush(regBrush);
        if(vexes[i]->nexts.size()==2){
            vexes[i]->left=vexes[i]->nexts[0]->center.rx()<vexes[i]->nexts[1]->center.rx()?vexes[i]->nexts[0]:vexes[i]->nexts[1];
            vexes[i]->right=vexes[i]->nexts[0]->center.rx()<vexes[i]->nexts[1]->center.rx()?vexes[i]->nexts[1]:vexes[i]->nexts[0];
        }else if(vexes[i]->nexts.size()==1){
            if(vexes[i]->nexts[0]->center.rx()<vexes[i]->center.rx()){
                vexes[i]->left=vexes[i]->nexts[0];
            }else{
                vexes[i]->right=vexes[i]->nexts[0];
            }
        }
    }

    //if experienced morris,delete nullVexes and their lines
    if(!nullVexes.empty()){
        for(int i=0;i<leaves.size();i++){
            leaves[i]->left=nullptr;
            leaves[i]->right=nullptr;
        }

        for(int i=0;i<halfLeaves.size();i++){
            if(halfLeaves[i]->left->nameText=="nullptr"){
                halfLeaves[i]->left=nullptr;
            }else{
                halfLeaves[i]->right=nullptr;
            }
        }

        int j=nullVexes.size();
        for(int i=0;i<j;i++)
        {
            myGraphicsScene->removeItem(nullVexes[i]->nameTag);
            if(nullVexes[i]->nameTag != nullptr)
            {
              delete nullVexes[i]->nameTag;
              nullVexes[i]->nameTag = nullptr;
            }
            myGraphicsScene->removeItem(nullVexes[i]);
            if(nullVexes[i] != nullptr)
            {
              delete nullVexes[i];
              nullVexes[i] = nullptr;
            }
        }
        nullVexes.clear();

        j=leafLines.size();
        for(int i=0;i<j;i++)
        {
            myGraphicsScene->removeItem(leafLines[i]);
            if(leafLines[i] != nullptr)
            {
              delete leafLines[i];
              leafLines[i] = nullptr;
            }
        }
        leafLines.clear();
    }
}

void MyGraphicsView::buildTree2()
{
    //if experienced morris,delete nullVexes and their lines
    if(!nullVexes.empty()){
        for(int i=0;i<leaves.size();i++){
            leaves[i]->left=nullptr;
            leaves[i]->right=nullptr;
        }

        for(int i=0;i<halfLeaves.size();i++){
            if(halfLeaves[i]->left->nameText=="nullptr"){
                halfLeaves[i]->left=nullptr;
            }else{
                halfLeaves[i]->right=nullptr;
            }
        }

        int j=nullVexes.size();
        for(int i=0;i<j;i++)
        {
            myGraphicsScene->removeItem(nullVexes[i]->nameTag);
            if(nullVexes[i]->nameTag != nullptr)
            {
              delete nullVexes[i]->nameTag;
              nullVexes[i]->nameTag = nullptr;
            }
            myGraphicsScene->removeItem(nullVexes[i]);
            if(nullVexes[i] != nullptr)
            {
              delete nullVexes[i];
              nullVexes[i] = nullptr;
            }
        }
        nullVexes.clear();

        j=leafLines.size();
        for(int i=0;i<j;i++)
        {
            myGraphicsScene->removeItem(leafLines[i]);
            if(leafLines[i] != nullptr)
            {
              delete leafLines[i];
              leafLines[i] = nullptr;
            }
        }
        leafLines.clear();
    }

    for(int i=0;i<vexes.size();i++)
    {
        vexes[i]->setBrush(regBrush);
        if(vexes[i]->nexts.size()==2){
            vexes[i]->left=vexes[i]->nexts[0]->center.rx()<vexes[i]->nexts[1]->center.rx()?vexes[i]->nexts[0]:vexes[i]->nexts[1];
            vexes[i]->right=vexes[i]->nexts[0]->center.rx()<vexes[i]->nexts[1]->center.rx()?vexes[i]->nexts[1]:vexes[i]->nexts[0];
        }else{
            qreal x=vexes[i]->center.rx();
            qreal y=vexes[i]->center.ry();
            QPointF center1(x-70,y+140);
            QPointF center2(x+70,y+170);

            if(vexes[i]->nexts.size()==1){
                if(vexes[i]->nexts[0]->center.rx()<vexes[i]->center.rx()){
                    vexes[i]->left=vexes[i]->nexts[0];
                    MyGraphicsVexItem *next2 = new MyGraphicsVexItem(center2);
                    myGraphicsScene->addItem(next2);
                    myGraphicsScene->addItem(next2->nameTag);
                    vexes[i]->right=next2;

                    nullVexes.push_back(next2);
                    leafLines.push_back(addLine(vexes[i],next2));
                }else{
                    vexes[i]->right=vexes[i]->nexts[0];
                    MyGraphicsVexItem *next1 = new MyGraphicsVexItem(center1);
                    myGraphicsScene->addItem(next1);
                    myGraphicsScene->addItem(next1->nameTag);

                    vexes[i]->left=next1;

                    nullVexes.push_back(next1);
                    leafLines.push_back(addLine(vexes[i],next1));
                }
                halfLeaves.push_back(vexes[i]);
            }else if(vexes[i]->nexts.size()==0){

                MyGraphicsVexItem *next1 = new MyGraphicsVexItem(center1);
                myGraphicsScene->addItem(next1);
                myGraphicsScene->addItem(next1->nameTag);


                MyGraphicsVexItem *next2 = new MyGraphicsVexItem(center2);
                myGraphicsScene->addItem(next2);
                myGraphicsScene->addItem(next2->nameTag);

                vexes[i]->left=next1;
                vexes[i]->right=next2;

                leaves.push_back(vexes[i]);

                nullVexes.push_back(next1);
                nullVexes.push_back(next2);

                leafLines.push_back(addLine(vexes[i],next1));
                leafLines.push_back(addLine(vexes[i],next2));
            }
        }
    }
}

void MyGraphicsView::pre(MyGraphicsVexItem * head)
{
    if(head!=nullptr){
        QStack<MyGraphicsVexItem*> s;
        s.push(head);
        while(!s.empty())
        {
            head=s.top();
            s.pop();
            addAnimation(head->visit());
            if(head->right!=nullptr){
                s.push(head->right);
            }
            if(head->left!=nullptr){
                s.push(head->left);
            }
        }
    }
}

void MyGraphicsView::in(MyGraphicsVexItem * head)
{
    if(head!=nullptr){
        QStack<MyGraphicsVexItem*> s;
        while(!s.empty() || head!=nullptr)
        {
            if(head!=nullptr) {
                s.push(head);
                head = head->left;
            }else{
                head=s.top();
                s.pop();
                addAnimation(head->visit());
                head=head->right;
            }
        }
    }
}

void MyGraphicsView::pos(MyGraphicsVexItem * head)
{
    if(head!=nullptr){
        QStack<MyGraphicsVexItem*> s;
        QStack<MyGraphicsVexItem*> col;
        s.push(head);
        while(!s.empty())
        {
            head=s.top();
            s.pop();
            col.push(head);
            if(head->left!=nullptr){
                s.push(head->left);
            }
            if(head->right!=nullptr){
                s.push(head->right);
            }
        }
        while(!col.empty())
        {
            addAnimation(col.top()->visit());
            col.pop();
        }
    }
}

QTimeLine* MyGraphicsView::changeName(QString s,MyGraphicsVexItem * head)
{
    QTimeLine *timeLine = new QTimeLine(500, this);
    timeLine->setFrameRange(0, 200);
    QEasingCurve curve = QEasingCurve::OutBounce;
    qreal baseRadius = 26;
    qreal difRadius = -6;
    connect(timeLine, &QTimeLine::frameChanged, timeLine, [=](int frame){
        myGraphicsScene->removeItem(head->nameTag);
        if(head->nameTag != nullptr)
           {
              delete head->nameTag;
              head->nameTag = nullptr;
           }
        head->setName(s);
        myGraphicsScene->addItem(head->nameTag);
        qreal curProgress = curve.valueForProgress(frame / 200.0);
        qreal curRadius = baseRadius + difRadius * curProgress;//20
        head->setRect(QRectF(head->center.rx() - curRadius, head->center.ry() - curRadius, curRadius * 2, curRadius * 2));
    });

    head->nameText=s;
    return timeLine;
}

void MyGraphicsView::morris(MyGraphicsVexItem * head)
{
    MyGraphicsVexItem * cur = head;
    MyGraphicsVexItem * mostRight = nullptr;//the rightmost node of cur's left child

    while (cur!=nullptr && cur->nameText != "nullptr") { //when cur is nullptr,stop
        addAnimation(cur->visit());
        mostRight = cur->left;
        if (mostRight != nullptr && mostRight->nameText != "nullptr")
        { //cur has left subtree
            while (mostRight->right->nameText != "nullptr" && mostRight->right->nameText != cur->nameText) { //找左树上最右节点
                mostRight = mostRight->right;
            }
            if (mostRight->right->nameText == "nullptr") { //arrived cur for the first time
                addAnimation(changeName(cur->nameText,mostRight->right));
                cur = cur->left;
                continue;
            } else { //second time
                addAnimation(changeName("nullptr",mostRight->right));
            }
        }
        //cur has no left subtree,or come to cur for the second time
        if(cur->right->nameText=="nullptr"){
            cur=cur->right;
        }else{
            for(int i=0;i<vexes.size();i++)
            {
                if(vexes[i]->nameText==cur->right->nameText){
                    cur=vexes[i];
                    break;
                }
            }
        }
    }
}

void MyGraphicsView::init()
{
    if(myGraphicsScene != nullptr)
    {
      delete myGraphicsScene;
      myGraphicsScene = nullptr;
    }

    aniQueue.clear();
    onAni = false;
    curAni = nullptr;

    vexID = 0;
    isCreating = false;

    vexes.clear();
    preVexes.clear();
    leaves.clear();
    nullVexes.clear();
    leafLines.clear();

    strtVex = nullptr;
    sketchItem = nullptr;

    myGraphicsScene = new QGraphicsScene();
    myGraphicsScene->setBackgroundBrush(Qt::transparent);
    myGraphicsScene->setSceneRect(0,0,1183,875);
    this->setScene(myGraphicsScene);

    root=new MyGraphicsVexItem(QPointF(590,150),10, vexID++);
    myGraphicsScene->addItem(root->nameTag);
    myGraphicsScene->addItem(root);
    vexes.push_back(root);
}

//*******************************************************************************************

MyGraphicsVexItem::MyGraphicsVexItem(QPointF _center, qreal _r, int nameID, QGraphicsItem *parent) :
    QGraphicsEllipseItem(_center.x()-20, _center.y()-20, 40, 40, parent),
    center(_center),
    radius(_r){
    nameText = QString::asprintf("V%d", nameID);
    nameTag = new QGraphicsSimpleTextItem();
    nameTag->setPos(center + QPointF(radius, - radius - QFontMetrics(nameFont).height()));
    nameTag->setFont(nameFont);
    nameTag->setText(nameText);
    nameTag->setZValue(this->zValue());
    nameTag->setBrush(Qt::black);
    nameTag->setFlags(QGraphicsItem::ItemIsSelectable);
    this->setPen(Qt::NoPen);
    this->setBrush(regBrush);
}

MyGraphicsVexItem::MyGraphicsVexItem(QPointF _center, qreal _r, QGraphicsItem *parent) :
    QGraphicsEllipseItem(_center.x()-20, _center.y()-20, 40, 40, parent),
    center(_center),
    radius(_r){
    nameText = "nullptr";
    nameTag = new QGraphicsSimpleTextItem();
    nameTag->setPos(center + QPointF(radius, - radius - QFontMetrics(nameFont).height()));
    nameTag->setFont(nameFont);
    nameTag->setText(nameText);
    nameTag->setZValue(this->zValue());
    nameTag->setBrush(Qt::black);
    QPen pen(QColor(108,166,205));
    pen.setStyle(Qt::DashLine);
    pen.setWidth(3);
    this->setPen(pen);
    this->setBrush(QColor(255,255,255));
}

void MyGraphicsVexItem::setName(QString s)
{
    nameText = s;
    nameTag = new QGraphicsSimpleTextItem();
    nameTag->setPos(this->center + QPointF(10, - 10 - QFontMetrics(nameFont).height()));
    nameTag->setFont(nameFont);
    nameTag->setText(nameText);
    nameTag->setZValue(this->zValue());
    nameTag->setBrush(Qt::black);
    nameTag->setFlags(QGraphicsItem::ItemIsSelectable);
}

QTimeLine* MyGraphicsVexItem::visit()
{
    QTimeLine *timeLine = new QTimeLine(500, this);
    timeLine->setFrameRange(0, 200);
    QEasingCurve curve = QEasingCurve::OutBounce;
    qreal baseRadius = 26;
    qreal difRadius = -6;
    connect(timeLine, &QTimeLine::frameChanged, timeLine, [=](int frame){
        this->setBrush(visitedBrush);
        qreal curProgress = curve.valueForProgress(frame / 200.0);
        qreal curRadius = baseRadius + difRadius * curProgress;//20
        this->setRect(QRectF(center.x() - curRadius, center.y() - curRadius, curRadius * 2, curRadius * 2));
    });
    return timeLine;
}

void MyGraphicsVexItem::showAnimation(){
    QTimeLine *timeLine = new QTimeLine(500, this);
    timeLine->setFrameRange(0, 200);
    QEasingCurve curve = QEasingCurve::OutBounce;
    qreal baseRadius = 26;
    qreal difRadius = -6;
    connect(timeLine, &QTimeLine::frameChanged, timeLine, [=](int frame){
        qreal curProgress = curve.valueForProgress(frame / 200.0);
        qreal curRadius = baseRadius + difRadius * curProgress;//20
        this->setRect(QRectF(center.x() - curRadius, center.y() - curRadius, curRadius * 2, curRadius * 2));
    });
    curAnimation = timeLine;
    startAnimation();
}

void MyGraphicsVexItem::startAnimation(){
    if(curAnimation != nullptr){
        curAnimation->start();
    }
}

//*******************************************************************************************

MyGraphicsLineItem::MyGraphicsLineItem(MyGraphicsVexItem *start, MyGraphicsVexItem *end, QGraphicsItem *parent) :
    QGraphicsLineItem(parent),
    startVex(start),
    endVex(end){
    //Set display effect
    defaultPen.setWidth(lineWidth);
    defaultPen.setStyle(lineStyle);
    defaultPen.setCapStyle(capStyle);
    defaultPen.setColor(defaultColor);
    this->setPen(defaultPen);
    this->setLine(startVex->center.rx(),startVex->center.ry(),endVex->center.rx(),endVex->center.ry());
    this->setZValue(-2);
}






