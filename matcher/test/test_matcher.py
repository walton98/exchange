import pytest

from matcher_client import MatcherClient
from matcher_pb2 import Book, Action, CreateBook, Snapshot

MCAST_GRP = "224.1.1.1"
MCAST_PORT = 30001
# allow upto two hops
MULTICAST_TTL = 2


@pytest.fixture(scope="session")
def matcher_client() -> MatcherClient:
    return MatcherClient(MCAST_GRP, MCAST_PORT, MULTICAST_TTL)


def snapshot_request() -> None:
    return Action(snapshot=Snapshot())


def snapshot(matcher_client: MatcherClient):
    matcher_client.send_request(snapshot_request())


def create_book(id: int) -> Action:
    book = Book()
    book.id = id
    create_book = CreateBook(book=book)
    return Action(create_book=create_book)


def test_create_book(matcher_client: MatcherClient) -> None:
    action = create_book(69)
    matcher_client.send_request(action)


def test_snapshot(matcher_client: MatcherClient) -> None:
    snapshot(matcher_client)
