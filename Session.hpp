#pragma once
#include "kuzco/Kuzco.hpp"

template <typename T>
class StateRoot : private kuzco::Root<T> {
public:
    using Root<T>::Root;

    struct Transaction {
    public:
        Transaction(StateRoot& r)
            : m_ptr(r.beginTransaction())
            , m_root(r)
        {}

        Transaction(const Transaction&) = delete;
        Transaction& operator=(const Transaction&) = delete;
        Transaction(Transaction&&) = delete;
        Transaction& operator=(Transaction&&) = delete;

        void cancel() { m_cancelled = true; }

        T* operator->() { return m_ptr; }
        T& operator*() { return *m_ptr; }

        ~Transaction() {
            bool store = !m_cancelled && !std::uncaught_exceptions();
            m_root.endTransaction(store);
        }
    private:
        T* m_ptr;
        StateRoot& m_root;
        bool m_cancelled = false;
    };

    Transaction transaction() {
        return Transaction(*this);
    }

    using Root<T>::detach;
    using Root<T>::detachedPayload;
private:
    void endTransaction(bool store) {
        Root<T>::endTransaction(store);
        if (store) {
            // only notify on stored transactions
            Publisher<StateRoot<T>>::notifySubscribers(*this);
        }
    }
};

class ForwardDeclared;

using FRoot = StateRoot<ForwardDeclared>;

struct Session
{
    Session();
    ~Session();
    FRoot m_froot;
};
