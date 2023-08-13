#ifndef _STRBLOB_H_
#define _STRBLOB_H_

class StrBlobPtr;

// 这个类其实是用智能指针指向了一个vector<string>对象
class StrBlob
{
    friend class StrBlobPtr;
public:
    StrBlobPtr begin(); /*{ return StrBlobPtr(*this); }*/
    StrBlobPtr end();
    /*{
        auto ret = StrBlobPtr(*this, data->size());
        return ret;
    }*/
public:
    typedef std::vector<std::string>::size_type size_type;
    StrBlob():data(std::make_shared<std::vector<std::string>>()) {};
    StrBlob(std::initializer_list<std::string> il):data(std::make_shared<std::vector<std::string>>(il)){}
    size_type size() const { return data->size(); }
    bool empty() const { return data->empty(); }
    // 添加删除元素
    void push_back(const std::string& str) { data->push_back(str); };
    void pop_back();
    // 元素访问
    std::string& front();
    std::string& back();
    // const 重载
    std::string& front() const;
    std::string& back() const;
private:
    std::shared_ptr<std::vector<std::string>> data;
    // 如果data[i]不合法 抛出一个异常
    void check(size_type i, const std::string& msg) const;
};

class StrBlobPtr
{
public:
    StrBlobPtr():curr(0){}
    StrBlobPtr(StrBlob& a, std::size_t sz = 0):wptr(a.data),curr(sz){}
    std::string& deref() const;
    StrBlobPtr& incr();
private:
    // 检查成功 返回一个指向vector的shared_ptr
    std::shared_ptr<std::vector<std::string>> check(std::size_t, const std::string&) const;
    // 保存一个weak_ptr，意味着底层vector可能会被销毁
    std::weak_ptr<std::vector<std::string>> wptr;
    size_t curr;
};

inline StrBlobPtr StrBlob::begin()
{ return StrBlobPtr(*this); }

inline StrBlobPtr StrBlob::end()
{
    auto ret = StrBlobPtr(*this, data->size());
    return ret;
}

#endif
